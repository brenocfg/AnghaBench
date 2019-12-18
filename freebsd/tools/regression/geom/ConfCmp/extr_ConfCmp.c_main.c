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
struct mytree {int /*<<< orphan*/  top; } ;

/* Variables and functions */
 int compare_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mytree* dofile (char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fsubs ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sort_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv)
{
	struct mytree *t1, *t2;
	int i;

	fsubs = fopen("_.subs", "w");
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	if (argc != 3)
		errx(1, "usage: %s file1 file2", argv[0]);

	t1 = dofile(argv[1]);
	if (t1 == NULL)
		errx(2, "XML parser error on file %s", argv[1]);
	sort_node(t1->top);
	t2 = dofile(argv[2]);
	if (t2 == NULL)
		errx(2, "XML parser error on file %s", argv[2]);
	sort_node(t2->top);
	i = compare_node(t1->top, t2->top, 0);
	return (i);
}