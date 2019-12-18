#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct blame_scoreboard {char const* final_buf; int final_buf_size; } ;
struct blame_origin {TYPE_2__* commit; } ;
struct blame_entry {int s_lno; int lno; int num_lines; struct blame_origin* suspect; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int OUTPUT_LINE_PORCELAIN ; 
 char* blame_nth_line (struct blame_scoreboard*,int) ; 
 int /*<<< orphan*/  emit_porcelain_details (struct blame_origin*,int) ; 
 int /*<<< orphan*/  oid_to_hex_r (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void emit_porcelain(struct blame_scoreboard *sb, struct blame_entry *ent,
			   int opt)
{
	int repeat = opt & OUTPUT_LINE_PORCELAIN;
	int cnt;
	const char *cp;
	struct blame_origin *suspect = ent->suspect;
	char hex[GIT_MAX_HEXSZ + 1];

	oid_to_hex_r(hex, &suspect->commit->object.oid);
	printf("%s %d %d %d\n",
	       hex,
	       ent->s_lno + 1,
	       ent->lno + 1,
	       ent->num_lines);
	emit_porcelain_details(suspect, repeat);

	cp = blame_nth_line(sb, ent->lno);
	for (cnt = 0; cnt < ent->num_lines; cnt++) {
		char ch;
		if (cnt) {
			printf("%s %d %d\n", hex,
			       ent->s_lno + 1 + cnt,
			       ent->lno + 1 + cnt);
			if (repeat)
				emit_porcelain_details(suspect, 1);
		}
		putchar('\t');
		do {
			ch = *cp++;
			putchar(ch);
		} while (ch != '\n' &&
			 cp < sb->final_buf + sb->final_buf_size);
	}

	if (sb->final_buf_size && cp[-1] != '\n')
		putchar('\n');
}