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
struct credential {char* username; char* password; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void print_entry(struct credential *c)
{
	printf("username=%s\n", c->username);
	printf("password=%s\n", c->password);
}