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
 int /*<<< orphan*/  M_IPSEC_SP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SP_INITREF (struct secpolicy*) ; 
 struct secpolicy* malloc (int,int /*<<< orphan*/ ,int) ; 

struct secpolicy *
key_newsp(void)
{
	struct secpolicy *sp;

	sp = malloc(sizeof(*sp), M_IPSEC_SP, M_NOWAIT | M_ZERO);
	if (sp != NULL)
		SP_INITREF(sp);
	return (sp);
}