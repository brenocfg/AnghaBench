#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ daddr_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  TYPE_1__* blist_t ;
struct TYPE_10__ {scalar_t__ bl_radix; } ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int BLIST_META_RADIX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ blist_alloc (TYPE_1__*,int*,int) ; 
 scalar_t__ blist_avail (TYPE_1__*) ; 
 TYPE_1__* blist_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blist_fill (TYPE_1__*,long long,int) ; 
 int /*<<< orphan*/  blist_free (TYPE_1__*,long long,int) ; 
 int /*<<< orphan*/  blist_print (TYPE_1__*) ; 
 int /*<<< orphan*/  blist_resize (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blist_stats (TYPE_1__*,struct sbuf*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int sscanf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int ac, char **av)
{
	int size = BLIST_META_RADIX * BLIST_BMAP_RADIX;
	int i;
	blist_t bl;
	struct sbuf *s;

	for (i = 1; i < ac; ++i) {
		const char *ptr = av[i];
		if (*ptr != '-') {
			size = strtol(ptr, NULL, 0);
			continue;
		}
		ptr += 2;
		fprintf(stderr, "Bad option: %s\n", ptr - 2);
		exit(1);
	}
	bl = blist_create(size, M_WAITOK);
	blist_free(bl, 0, size);

	for (;;) {
		char buf[1024];
		long long da = 0;
		int count = 0, maxcount = 0;

		printf("%lld/%lld/%lld> ", (long long)blist_avail(bl),
		    (long long)size, (long long)bl->bl_radix);
		fflush(stdout);
		if (fgets(buf, sizeof(buf), stdin) == NULL)
			break;
		switch(buf[0]) {
		case 'r':
			if (sscanf(buf + 1, "%d", &count) == 1) {
				blist_resize(&bl, count, 1, M_WAITOK);
			} else {
				printf("?\n");
			}
		case 'p':
			blist_print(bl);
			break;
		case 's':
			s = sbuf_new_auto();
			blist_stats(bl, s);
			sbuf_finish(s);
			printf("%s", sbuf_data(s));
			sbuf_delete(s);
			break;
		case 'a':
			if (sscanf(buf + 1, "%d%d", &count, &maxcount) == 2) {
				daddr_t blk = blist_alloc(bl, &count, maxcount);
				printf("    R=%08llx, c=%08d\n",
				    (long long)blk, count);
			} else {
				printf("?\n");
			}
			break;
		case 'f':
			if (sscanf(buf + 1, "%llx %d", &da, &count) == 2) {
				blist_free(bl, da, count);
			} else {
				printf("?\n");
			}
			break;
		case 'l':
			if (sscanf(buf + 1, "%llx %d", &da, &count) == 2) {
				printf("    n=%jd\n",
				    (intmax_t)blist_fill(bl, da, count));
			} else {
				printf("?\n");
			}
			break;
		case '?':
		case 'h':
			puts(
			    "p          -print\n"
			    "s          -stats\n"
			    "a %d %d    -allocate\n"
			    "f %x %d    -free\n"
			    "l %x %d    -fill\n"
			    "r %d       -resize\n"
			    "h/?        -help\n"
			    "q          -quit"
			);
			break;
		case 'q':
			break;
		default:
			printf("?\n");
			break;
		}
		if (buf[0] == 'q')
			break;
	}
	return (0);
}