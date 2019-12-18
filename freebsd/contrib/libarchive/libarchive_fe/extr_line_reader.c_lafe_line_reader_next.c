#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lafe_line_reader {char* line_end; char* buff_end; char* line_start; char* buff; int buff_length; int /*<<< orphan*/ * f; int /*<<< orphan*/  pathname; scalar_t__ nullSeparator; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_line_reader_find_eol (struct lafe_line_reader*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/ * stdin ; 

const char *
lafe_line_reader_next(struct lafe_line_reader *lr)
{
	size_t bytes_wanted, bytes_read, new_buff_size;
	char *line_start, *p;

	for (;;) {
		/* If there's a line in the buffer, return it immediately. */
		while (lr->line_end < lr->buff_end) {
			line_start = lr->line_start;
			lr->line_start = ++lr->line_end;
			lafe_line_reader_find_eol(lr);

			if (lr->nullSeparator || line_start[0] != '\0')
				return (line_start);
		}

		/* If we're at end-of-file, process the final data. */
		if (lr->f == NULL) {
			if (lr->line_start == lr->buff_end)
				return (NULL); /* No more text */
			line_start = lr->line_start;
			lr->line_start = lr->buff_end;
			return (line_start);
		}

		/* Buffer only has part of a line. */
		if (lr->line_start > lr->buff) {
			/* Move a leftover fractional line to the beginning. */
			memmove(lr->buff, lr->line_start,
			    lr->buff_end - lr->line_start);
			lr->buff_end -= lr->line_start - lr->buff;
			lr->line_end -= lr->line_start - lr->buff;
			lr->line_start = lr->buff;
		} else {
			/* Line is too big; enlarge the buffer. */
			new_buff_size = lr->buff_length * 2;
			if (new_buff_size <= lr->buff_length)
				lafe_errc(1, ENOMEM,
				    "Line too long in %s", lr->pathname);
			lr->buff_length = new_buff_size;
			/*
			 * Allocate one extra byte to allow terminating
			 * the buffer.
			 */
			p = realloc(lr->buff, new_buff_size + 1);
			if (p == NULL)
				lafe_errc(1, ENOMEM,
				    "Line too long in %s", lr->pathname);
			lr->buff_end = p + (lr->buff_end - lr->buff);
			lr->line_end = p + (lr->line_end - lr->buff);
			lr->line_start = lr->buff = p;
		}

		/* Get some more data into the buffer. */
		bytes_wanted = lr->buff + lr->buff_length - lr->buff_end;
		bytes_read = fread(lr->buff_end, 1, bytes_wanted, lr->f);
		lr->buff_end += bytes_read;
		*lr->buff_end = '\0'; /* Always terminate buffer */
		lafe_line_reader_find_eol(lr);

		if (ferror(lr->f))
			lafe_errc(1, errno, "Can't read %s", lr->pathname);
		if (feof(lr->f)) {
			if (lr->f != stdin)
				fclose(lr->f);
			lr->f = NULL;
		}
	}
}