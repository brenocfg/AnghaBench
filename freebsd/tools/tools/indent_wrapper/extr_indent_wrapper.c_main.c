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
typedef  scalar_t__ uint64_t ;
typedef  int uint16_t ;
struct block {int* mask; int* data; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  cmdbuf ;
typedef  int /*<<< orphan*/  block_head_t ;

/* Variables and functions */
 int BLOCK_ADD ; 
 int BLOCK_MASK ; 
 scalar_t__ BLOCK_SIZE ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct block*,int /*<<< orphan*/ ) ; 
 struct block* alloc_block () ; 
 int /*<<< orphan*/  cmd_block_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ diff_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ diff_tool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_block (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  isprint (int) ; 
 char* opt_diff_tool ; 
 scalar_t__ opt_verbose ; 
 char* optarg ; 
 int peek_block (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_block (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe ; 
 scalar_t__ size_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	block_head_t diff_head;
	block_head_t diff_a_head;
	block_head_t diff_b_head;
	block_head_t indent_in_head;
	block_head_t indent_out_head;
	struct block *p1 = NULL;
	struct block *p2 = NULL;
	uint64_t size;
	uint64_t x;
	uint64_t y1 = 0;
	uint64_t y2 = 0;
	int recurse = 0;
	int inside_string = 0;
	int escape_char = 0;
	int do_parse = 0;
	char cmdbuf[256];
	uint16_t ch;
	uint16_t chn;
	int c;
	int retval = 0;

	signal(SIGPIPE, &sigpipe);

	cmdbuf[0] = 0;

	while ((c = getopt(argc, argv, "dDvg:s:c:ht:")) != -1) {
		switch (c) {
		case 'v':
			opt_verbose++;
			break;
		case 't':
			opt_diff_tool = optarg;
			break;
		case 'g':
			snprintf(cmdbuf, sizeof(cmdbuf), "git show -U1000000 %s", optarg);
			break;
		case 'd':
			snprintf(cmdbuf, sizeof(cmdbuf), "git diff -U1000000");
			break;
		case 'D':
			snprintf(cmdbuf, sizeof(cmdbuf), "svn diff --diff-cmd=diff -x -U1000000");
			break;
		case 's':
			snprintf(cmdbuf, sizeof(cmdbuf), "svn diff --diff-cmd=diff -x -U1000000 -r %s", optarg);
			break;
		case 'c':
			snprintf(cmdbuf, sizeof(cmdbuf), "%s", optarg);
			break;
		default:
			usage();
		}
	}
	if (cmdbuf[0] == 0)
		usage();

	cmd_block_process(NULL, &diff_head, cmdbuf);

	TAILQ_INIT(&diff_a_head);
	TAILQ_INIT(&diff_b_head);

	size = size_block(&diff_head);
	p1 = alloc_block();
	y1 = 0;
	p2 = alloc_block();
	y2 = 0;

	for (x = 0; x < size;) {
		ch = peek_block(&diff_head, x);
		switch (ch & 0xFF) {
		case '+':
			if (ch == peek_block(&diff_head, x + 1) &&
			    ch == peek_block(&diff_head, x + 2) &&
			    ' ' == (peek_block(&diff_head, x + 3) & 0xFF))
				goto parse_filename;
			if (do_parse == 0)
				break;
			for (x++; x != size; x++) {
				ch = peek_block(&diff_head, x);
				p1->mask[y1] = BLOCK_ADD >> 8;
				p1->data[y1++] = ch;
				if (y1 == BLOCK_SIZE) {
					TAILQ_INSERT_TAIL(&diff_a_head, p1, entry);
					p1 = alloc_block();
					y1 = 0;
				}
				if ((ch & 0xFF) == '\n')
					break;
			}
			break;
		case '-':
			if (ch == peek_block(&diff_head, x + 1) &&
			    ch == peek_block(&diff_head, x + 2) &&
			    ' ' == (peek_block(&diff_head, x + 3) & 0xFF))
				goto parse_filename;
			if (do_parse == 0)
				break;
			for (x++; x != size; x++) {
				ch = peek_block(&diff_head, x);
				p2->data[y2++] = ch;
				if (y2 == BLOCK_SIZE) {
					TAILQ_INSERT_TAIL(&diff_b_head, p2, entry);
					p2 = alloc_block();
					y2 = 0;
				}
				if ((ch & 0xFF) == '\n')
					break;
			}
			break;
		case ' ':
			if (do_parse == 0)
				break;
			for (x++; x != size; x++) {
				ch = peek_block(&diff_head, x);
				p1->data[y1++] = ch;
				if (y1 == BLOCK_SIZE) {
					TAILQ_INSERT_TAIL(&diff_a_head, p1, entry);
					p1 = alloc_block();
					y1 = 0;
				}
				p2->data[y2++] = ch;
				if (y2 == BLOCK_SIZE) {
					TAILQ_INSERT_TAIL(&diff_b_head, p2, entry);
					p2 = alloc_block();
					y2 = 0;
				}
				if ((ch & 0xFF) == '\n')
					break;
			}
			break;
	parse_filename:
			for (x += 3; x != size; x++) {
				ch = peek_block(&diff_head, x);
				chn = peek_block(&diff_head, x + 1);
				if ((ch & 0xFF) == '.') {
					/* only accept .c and .h files */
					do_parse = ((chn & 0xFF) == 'c' || (chn & 0xFF) == 'h');
				}
				if ((ch & 0xFF) == '\n')
					break;
			}
		default:
			break;
		}
		/* skip till end of line */
		for (; x < size; x++) {
			ch = peek_block(&diff_head, x);
			if ((ch & 0xFF) == '\n') {
				x++;
				break;
			}
		}
	}
	p1->length = y1;
	p2->length = y2;
	TAILQ_INSERT_TAIL(&diff_a_head, p1, entry);
	TAILQ_INSERT_TAIL(&diff_b_head, p2, entry);

	/* first pass - verify input */
	size = size_block(&diff_a_head);
	for (x = 0; x != size; x++) {
		ch = peek_block(&diff_a_head, x) & 0xFF;
		if (!(ch & 0x80) && ch != '\t' && ch != '\r' && ch != '\n' &&
		    ch != ' ' && !isprint(ch))
			errx(EX_SOFTWARE, "Non printable characters are not allowed: '%c'", ch);
		else if (ch & 0x80) {
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
		}
	}

	/* second pass - identify all comments */
	for (x = 0; x < size; x++) {
		ch = peek_block(&diff_a_head, x);
		chn = peek_block(&diff_a_head, x + 1);
		if ((ch & 0xFF) == '/' && (chn & 0xFF) == '/') {
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
			set_block(&diff_a_head, x + 1, chn | BLOCK_MASK);
			for (x += 2; x < size; x++) {
				ch = peek_block(&diff_a_head, x);
				if ((ch & 0xFF) == '\n')
					break;
				set_block(&diff_a_head, x, ch | BLOCK_MASK);
			}
		} else if ((ch & 0xFF) == '/' && (chn & 0xFF) == '*') {
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
			set_block(&diff_a_head, x + 1, chn | BLOCK_MASK);
			for (x += 2; x < size; x++) {
				ch = peek_block(&diff_a_head, x);
				chn = peek_block(&diff_a_head, x + 1);
				if ((ch & 0xFF) == '*' && (chn & 0xFF) == '/') {
					set_block(&diff_a_head, x, ch | BLOCK_MASK);
					set_block(&diff_a_head, x + 1, chn | BLOCK_MASK);
					x++;
					break;
				}
				set_block(&diff_a_head, x, ch | BLOCK_MASK);
			}
		}
	}

	/* third pass - identify preprocessor tokens and strings */
	for (x = 0; x < size; x++) {
		ch = peek_block(&diff_a_head, x);
		if (ch & BLOCK_MASK)
			continue;
		if (inside_string == 0 && (ch & 0xFF) == '#') {
			int skip_newline = 0;

			set_block(&diff_a_head, x, ch | BLOCK_MASK);
			for (x++; x < size; x++) {
				ch = peek_block(&diff_a_head, x);
				if ((ch & 0xFF) == '\n') {
					if (!skip_newline)
						break;
					skip_newline = 0;
				}
				if (ch & BLOCK_MASK)
					continue;
				if ((ch & 0xFF) == '\\')
					skip_newline = 1;
				set_block(&diff_a_head, x, ch | BLOCK_MASK);
			}
		}
		if ((ch & 0xFF) == '"' || (ch & 0xFF) == '\'') {
			if (inside_string == 0) {
				inside_string = (ch & 0xFF);
			} else {
				if (escape_char == 0 && inside_string == (ch & 0xFF))
					inside_string = 0;
			}
			escape_char = 0;
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
		} else if (inside_string != 0) {
			if ((ch & 0xFF) == '\\')
				escape_char = !escape_char;
			else
				escape_char = 0;
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
		}
	}

	/* fourth pass - identify function blocks */
	if (opt_verbose > 0) {
		chn = peek_block(&diff_a_head, x);
		printf("L%02d%c|", recurse,
		    (chn & BLOCK_ADD) ? '+' : ' ');
	}
	for (x = 0; x < size; x++) {
		ch = peek_block(&diff_a_head, x);
		if (opt_verbose > 0) {
			printf("%c", ch & 0xFF);
			if ((ch & 0xFF) == '\n') {
				chn = peek_block(&diff_a_head, x + 1);
				printf("L%02d%c|", recurse,
				    (chn & BLOCK_ADD) ? '+' : ' ');
			}
		}
		if (ch & BLOCK_MASK)
			continue;
		switch (ch & 0xFF) {
		case '{':
		case '(':
			recurse++;
			break;
		default:
			break;
		}
		if (recurse != 0)
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
		switch (ch & 0xFF) {
		case '}':
		case ')':
			recurse--;
			break;
		default:
			break;
		}
	}
	if (opt_verbose > 0)
		printf("\n");
	if (recurse != 0)
		errx(EX_SOFTWARE, "Unbalanced parenthesis");
	if (inside_string != 0)
		errx(EX_SOFTWARE, "String without end");

	/* fifth pass - on the same line statements */
	for (x = 0; x < size; x++) {
		ch = peek_block(&diff_a_head, x);
		if (ch & BLOCK_MASK)
			continue;
		switch (ch & 0xFF) {
		case '\n':
			break;
		default:
			set_block(&diff_a_head, x, ch | BLOCK_MASK);
			break;
		}
	}

	/* sixth pass - output relevant blocks to indent */
	for (y1 = x = 0; x < size; x++) {
		ch = peek_block(&diff_a_head, x);
		if (ch & BLOCK_ADD) {
			TAILQ_INIT(&indent_in_head);

			p2 = alloc_block();
			y2 = 0;
			for (; y1 < size; y1++) {
				ch = peek_block(&diff_a_head, y1);
				if (y1 > x && !(ch & (BLOCK_MASK | BLOCK_ADD)))
					break;
				p2->data[y2++] = ch & 0xFF;
				if (y2 == BLOCK_SIZE) {
					TAILQ_INSERT_TAIL(&indent_in_head, p2, entry);
					p2 = alloc_block();
					y2 = 0;
				}
			}
			if (p2->data[y2] != '\n')
				p2->data[y2++] = '\n';
			p2->length = y2;
			TAILQ_INSERT_TAIL(&indent_in_head, p2, entry);

			cmd_block_process(&indent_in_head, &indent_out_head,
			    "indent "
			    "-Tbool "
			    "-Tclass "
			    "-TFILE "
			    "-TLIST_ENTRY "
			    "-TLIST_HEAD "
			    "-TSLIST_ENTRY "
			    "-TSLIST_HEAD "
			    "-TSTAILQ_ENTRY "
			    "-TSTAILQ_HEAD "
			    "-TTAILQ_ENTRY "
			    "-TTAILQ_HEAD "
			    "-T__aligned "
			    "-T__packed "
			    "-T__unused "
			    "-T__used "
			    "-Tfd_set "
			    "-Toss_mixerinfo "
			    "-Tu_char "
			    "-Tu_int "
			    "-Tu_long "
			    "-Tu_short "
			    "-ta -st -bad -bap -nbbb -nbc -br -nbs "
			    "-c41 -cd41 -cdb -ce -ci4 -cli0 -d0 -di8 -ndj -ei -nfc1 "
			    "-nfcb -i8 -ip8 -l79 -lc77 -ldi0 -nlp -npcs -psl -sc "
			    "-nsob -nv "
			    " | "
			    "sed "
			    "-e 's/_HEAD [(]/_HEAD(/g' "
			    "-e 's/_ENTRY [(]/_ENTRY(/g' "
			    "-e 's/\t__aligned/ __aligned/g' "
			    "-e 's/\t__packed/ __packed/g' "
			    "-e 's/\t__unused/ __unused/g' "
			    "-e 's/\t__used/ __used/g' "
			    "-e 's/^#define /#define\t/g'");

			if (opt_diff_tool != NULL) {
				if (diff_tool(&indent_in_head, &indent_out_head))
					retval = 1;
			} else {
				if (diff_block(&indent_in_head, &indent_out_head))
					retval = 1;
			}
			free_block(&indent_in_head);
			free_block(&indent_out_head);
			x = y1;
		} else if (!(ch & BLOCK_MASK)) {
			y1 = x + 1;
		}
	}
	return (retval);
}