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
struct me_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INIT (struct me_list*) ; 
 int ME_HASH_SIZE ; 
 int /*<<< orphan*/  M_IFME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct me_list* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct me_list *
me_hashinit(void)
{
	struct me_list *hash;
	int i;

	hash = malloc(sizeof(struct me_list) * ME_HASH_SIZE,
	    M_IFME, M_WAITOK);
	for (i = 0; i < ME_HASH_SIZE; i++)
		CK_LIST_INIT(&hash[i]);

	return (hash);
}