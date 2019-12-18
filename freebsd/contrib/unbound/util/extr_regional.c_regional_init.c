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
struct regional {char* data; scalar_t__ total_large; int /*<<< orphan*/ * large_list; int /*<<< orphan*/ * next; scalar_t__ first_size; scalar_t__ available; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNMENT ; 
 size_t ALIGN_UP (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
regional_init(struct regional* r)
{
	size_t a = ALIGN_UP(sizeof(struct regional), ALIGNMENT);
	r->data = (char*)r + a;
	r->available = r->first_size - a;
	r->next = NULL;
	r->large_list = NULL;
	r->total_large = 0;
}