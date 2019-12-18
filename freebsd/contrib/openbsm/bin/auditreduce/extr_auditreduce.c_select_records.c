#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_14__ {int /*<<< orphan*/  path; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {TYPE_2__ path; TYPE_1__ ipc; } ;
struct TYPE_16__ {int id; scalar_t__ len; TYPE_3__ tt; } ;
typedef  TYPE_4__ tokenstr_t ;
typedef  int /*<<< orphan*/  tok ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AUT_HEADER32 133 
#define  AUT_IPC 132 
#define  AUT_PATH 131 
#define  AUT_PROCESS32 130 
#define  AUT_RETURN32 129 
#define  AUT_SUBJECT32 128 
 scalar_t__ ISOPTSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_v ; 
 int au_fetch_tok (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int au_read_rec (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bcopy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int opttochk ; 
 int select_filepath (int /*<<< orphan*/ ,int*) ; 
 int select_hdr32 (TYPE_4__,int*) ; 
 int select_ipcobj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int select_proc32 (TYPE_4__,int*) ; 
 int select_return32 (TYPE_4__,TYPE_4__,int*) ; 
 int select_subj32 (TYPE_4__,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
select_records(FILE *fp)
{
	tokenstr_t tok_hdr32_copy;
	u_char *buf;
	tokenstr_t tok;
	int reclen;
	int bytesread;
	int selected;
	uint32_t optchkd;
	int print;

	int err = 0;
	while ((reclen = au_read_rec(fp, &buf)) != -1) {
		optchkd = 0;
		bytesread = 0;
		selected = 1;
		while ((selected == 1) && (bytesread < reclen)) {
			if (-1 == au_fetch_tok(&tok, buf + bytesread,
			    reclen - bytesread)) {
				/* Is this an incomplete record? */
				err = 1;
				break;
			}

			/*
			 * For each token type we have have different
			 * selection criteria.
			 */
			switch(tok.id) {
			case AUT_HEADER32:
					selected = select_hdr32(tok,
					    &optchkd);
					bcopy(&tok, &tok_hdr32_copy,
					    sizeof(tok));
					break;

			case AUT_PROCESS32:
					selected = select_proc32(tok,
					    &optchkd);
					break;

			case AUT_SUBJECT32:
					selected = select_subj32(tok,
					    &optchkd);
					break;

			case AUT_IPC:
					selected = select_ipcobj(
					    tok.tt.ipc.type, tok.tt.ipc.id,
					    &optchkd); 
					break;

			case AUT_PATH:
					selected = select_filepath(
					    tok.tt.path.path, &optchkd);
					break;	

			case AUT_RETURN32:
				selected = select_return32(tok,
				    tok_hdr32_copy, &optchkd);
				break;

			default:
				break;
			}
			bytesread += tok.len;
		}
		/* Check if all the options were matched. */
		print = ((selected == 1) && (!err) && (!(opttochk & ~optchkd)));
		if (ISOPTSET(opttochk, OPT_v))
			print = !print;
		if (print)
			(void) fwrite(buf, 1, reclen, stdout);
		free(buf);
	}
	return (0);
}