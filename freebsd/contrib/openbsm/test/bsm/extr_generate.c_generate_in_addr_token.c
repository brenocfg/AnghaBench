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
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/ * au_to_in_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ in_addr_token_addr ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_in_addr_token(const char *directory, const char *token_filename)
{
	token_t *in_addr_token;

	in_addr_token_addr.s_addr = inet_addr("192.168.100.15");

	in_addr_token = au_to_in_addr(&in_addr_token_addr);
	if (in_addr_token == NULL)
		err(EX_UNAVAILABLE, "au_to_in_addr");
	write_token(directory, token_filename, in_addr_token);
}