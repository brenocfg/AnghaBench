#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  TYPE_1__ tokenstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AUT_HEADER32 ; 
 int AU_OFLAG_XML ; 
 int au_fetch_tok (TYPE_1__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  au_print_flags_tok (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int au_read_rec (int /*<<< orphan*/ *,scalar_t__**) ; 
 char* del ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int oflags ; 
 scalar_t__ oneline ; 
 scalar_t__ partial ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  ungetc (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
print_tokens(FILE *fp)
{
	u_char *buf;
	tokenstr_t tok;
	int reclen;
	int bytesread;

	/* Allow tail -f | praudit to work. */
	if (partial) {
		u_char type = 0;
		/* Record must begin with a header token. */
		do {
			type = fgetc(fp);
		} while(type != AUT_HEADER32);
		ungetc(type, fp);
	}

	while ((reclen = au_read_rec(fp, &buf)) != -1) {
		bytesread = 0;
		while (bytesread < reclen) {
			/* Is this an incomplete record? */
			if (-1 == au_fetch_tok(&tok, buf + bytesread,
			    reclen - bytesread))
				break;
			au_print_flags_tok(stdout, &tok, del, oflags);
			bytesread += tok.len;
			if (oneline) {
				if (!(oflags & AU_OFLAG_XML))
					printf("%s", del);
			} else
				printf("\n");
		}
		free(buf);
		if (oneline)
			printf("\n");
		fflush(stdout);
	}
	return (0);
}