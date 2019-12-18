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
struct gre_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INIT (struct gre_list*) ; 
 int GRE_HASH_SIZE ; 
 int /*<<< orphan*/  M_GRE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct gre_list* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct gre_list *
gre_hashinit(void)
{
	struct gre_list *hash;
	int i;

	hash = malloc(sizeof(struct gre_list) * GRE_HASH_SIZE,
	    M_GRE, M_WAITOK);
	for (i = 0; i < GRE_HASH_SIZE; i++)
		CK_LIST_INIT(&hash[i]);

	return (hash);
}