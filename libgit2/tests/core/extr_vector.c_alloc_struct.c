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
struct TYPE_4__ {int content; scalar_t__ count; } ;
typedef  TYPE_1__ my_struct ;

/* Variables and functions */
 int /*<<< orphan*/  _struct_count ; 
 TYPE_1__* git__malloc (int) ; 

__attribute__((used)) static my_struct *alloc_struct(int value)
{
	my_struct *st = git__malloc(sizeof(my_struct));
	st->content = value;
	st->count = 0;
	_struct_count++;
	return st;
}