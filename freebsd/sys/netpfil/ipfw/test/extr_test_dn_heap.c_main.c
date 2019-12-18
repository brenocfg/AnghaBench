#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct dn_heap {scalar_t__ elements; TYPE_1__* p; } ;
typedef  int /*<<< orphan*/  h ;
struct TYPE_2__ {scalar_t__ key; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  bzero (struct dn_heap*,int) ; 
 int /*<<< orphan*/  heap_extract (struct dn_heap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_init (struct dn_heap*,int,int) ; 
 int /*<<< orphan*/  heap_insert (struct dn_heap*,int,void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int random () ; 
 int /*<<< orphan*/  test_hash () ; 

int
main(int argc, char *argv[])
{
	struct dn_heap h;
	int i, n, n2, n3;

	test_hash();
	return 0;

	/* n = elements, n2 = cycles */
	n = (argc > 1) ? atoi(argv[1]) : 0;
	if (n <= 0 || n > 1000000)
		n = 100;
	n2 = (argc > 2) ? atoi(argv[2]) : 0;
	if (n2 <= 0)
		n = 1000000;
	n3 = (argc > 3) ? atoi(argv[3]) : 0;
	bzero(&h, sizeof(h));
	heap_init(&h, n, -1);
	while (n2-- > 0) {
		uint64_t prevk = 0;
		for (i=0; i < n; i++)
			heap_insert(&h, n3 ? n-i: random(), (void *)(100+i));
		
		for (i=0; h.elements > 0; i++) {
			uint64_t k = h.p[0].key;
			if (k < prevk)
				panic("wrong sequence\n");
			prevk = k;
			if (0)
			printf("%d key %llu, val %p\n",
				i, h.p[0].key, h.p[0].object);
			heap_extract(&h, NULL);
		}
	}
	return 0;
}