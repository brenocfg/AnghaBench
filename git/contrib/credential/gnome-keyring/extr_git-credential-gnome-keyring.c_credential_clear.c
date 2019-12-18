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
struct credential {int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  path; int /*<<< orphan*/  host; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_init (struct credential*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnome_keyring_memory_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void credential_clear(struct credential *c)
{
	g_free(c->protocol);
	g_free(c->host);
	g_free(c->path);
	g_free(c->username);
	gnome_keyring_memory_free(c->password);

	credential_init(c);
}