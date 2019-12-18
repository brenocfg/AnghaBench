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
struct pc1_ctx {int /*<<< orphan*/  cle; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pc1_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pc1_init(struct pc1_ctx *pc1)
{
	memset(pc1, 0, sizeof(struct pc1_ctx));

	/* ('Remsaalps!123456') is the key used, you can change it */
	strcpy(pc1->cle, "Remsaalps!123456");
}