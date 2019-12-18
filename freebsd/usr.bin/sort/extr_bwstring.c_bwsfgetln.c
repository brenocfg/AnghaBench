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
typedef  int wint_t ;
typedef  scalar_t__ wchar_t ;
struct reader_buffer {int fgetwln_z_buffer_size; int* fgetwln_z_buffer; } ;
struct bwstring {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MB_CUR_MAX ; 
 int SIZEOF_WCHAR_STRING (int) ; 
 int WEOF ; 
 int btowc (char) ; 
 struct bwstring* bwscsbdup (unsigned char*,size_t) ; 
 struct bwstring* bwssbdup (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int fgetwc (int /*<<< orphan*/ *) ; 
 scalar_t__* fgetwln (int /*<<< orphan*/ *,size_t*) ; 
 void* sort_realloc (int*,int) ; 

struct bwstring *
bwsfgetln(FILE *f, size_t *len, bool zero_ended, struct reader_buffer *rb)
{
	wint_t eols;

	eols = zero_ended ? btowc('\0') : btowc('\n');

	if (!zero_ended && (MB_CUR_MAX > 1)) {
		wchar_t *ret;

		ret = fgetwln(f, len);

		if (ret == NULL) {
			if (!feof(f))
				err(2, NULL);
			return (NULL);
		}
		if (*len > 0) {
			if (ret[*len - 1] == (wchar_t)eols)
				--(*len);
		}
		return (bwssbdup(ret, *len));

	} else if (!zero_ended && (MB_CUR_MAX == 1)) {
		char *ret;

		ret = fgetln(f, len);

		if (ret == NULL) {
			if (!feof(f))
				err(2, NULL);
			return (NULL);
		}
		if (*len > 0) {
			if (ret[*len - 1] == '\n')
				--(*len);
		}
		return (bwscsbdup((unsigned char*)ret, *len));

	} else {
		*len = 0;

		if (feof(f))
			return (NULL);

		if (2 >= rb->fgetwln_z_buffer_size) {
			rb->fgetwln_z_buffer_size += 256;
			rb->fgetwln_z_buffer = sort_realloc(rb->fgetwln_z_buffer,
			    sizeof(wchar_t) * rb->fgetwln_z_buffer_size);
		}
		rb->fgetwln_z_buffer[*len] = 0;

		if (MB_CUR_MAX == 1)
			while (!feof(f)) {
				int c;

				c = fgetc(f);

				if (c == EOF) {
					if (*len == 0)
						return (NULL);
					goto line_read_done;
				}
				if (c == eols)
					goto line_read_done;

				if (*len + 1 >= rb->fgetwln_z_buffer_size) {
					rb->fgetwln_z_buffer_size += 256;
					rb->fgetwln_z_buffer = sort_realloc(rb->fgetwln_z_buffer,
					    SIZEOF_WCHAR_STRING(rb->fgetwln_z_buffer_size));
				}

				rb->fgetwln_z_buffer[*len] = c;
				rb->fgetwln_z_buffer[++(*len)] = 0;
			}
		else
			while (!feof(f)) {
				wint_t c = 0;

				c = fgetwc(f);

				if (c == WEOF) {
					if (*len == 0)
						return (NULL);
					goto line_read_done;
				}
				if (c == eols)
					goto line_read_done;

				if (*len + 1 >= rb->fgetwln_z_buffer_size) {
					rb->fgetwln_z_buffer_size += 256;
					rb->fgetwln_z_buffer = sort_realloc(rb->fgetwln_z_buffer,
					    SIZEOF_WCHAR_STRING(rb->fgetwln_z_buffer_size));
				}

				rb->fgetwln_z_buffer[*len] = c;
				rb->fgetwln_z_buffer[++(*len)] = 0;
			}

line_read_done:
		/* we do not count the last 0 */
		return (bwssbdup(rb->fgetwln_z_buffer, *len));
	}
}