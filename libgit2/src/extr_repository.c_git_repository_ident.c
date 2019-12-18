#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ident_name; char* ident_email; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */

int git_repository_ident(const char **name, const char **email, const git_repository *repo)
{
	*name = repo->ident_name;
	*email = repo->ident_email;

	return 0;
}