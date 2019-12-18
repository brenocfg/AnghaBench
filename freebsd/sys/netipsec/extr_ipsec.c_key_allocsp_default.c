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
struct secpolicy {int dummy; } ;

/* Variables and functions */
 struct secpolicy* V_def_policy ; 
 int /*<<< orphan*/  key_addref (struct secpolicy*) ; 

__attribute__((used)) static struct secpolicy *
key_allocsp_default(void)
{

	key_addref(V_def_policy);
	return (V_def_policy);
}