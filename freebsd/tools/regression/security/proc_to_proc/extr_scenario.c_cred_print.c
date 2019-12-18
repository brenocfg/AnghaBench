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
struct cred {int cr_euid; int cr_ruid; int cr_svuid; int cr_issetugid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

__attribute__((used)) static void
cred_print(FILE *output, struct cred *cred)
{

	fprintf(output, "(e:%d r:%d s:%d P_SUGID:%d)", cred->cr_euid,
	    cred->cr_ruid, cred->cr_svuid, cred->cr_issetugid);
}