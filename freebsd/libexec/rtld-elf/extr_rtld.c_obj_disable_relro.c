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
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int PROT_READ ; 
 int PROT_WRITE ; 
 int obj_remap_relro (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
obj_disable_relro(Obj_Entry *obj)
{

	return (obj_remap_relro(obj, PROT_READ | PROT_WRITE));
}