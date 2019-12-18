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
struct credential {scalar_t__ path; scalar_t__ port; scalar_t__ host; scalar_t__ protocol; scalar_t__ username; } ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_free ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  g_strdup (scalar_t__) ; 
 int /*<<< orphan*/  g_strdup_printf (char*,scalar_t__) ; 

__attribute__((used)) static GHashTable *make_attr_list(struct credential *c)
{
	GHashTable *al = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

	if (c->username)
		g_hash_table_insert(al, "user", g_strdup(c->username));
	if (c->protocol)
		g_hash_table_insert(al, "protocol", g_strdup(c->protocol));
	if (c->host)
		g_hash_table_insert(al, "server", g_strdup(c->host));
	if (c->port)
		g_hash_table_insert(al, "port", g_strdup_printf("%hu", c->port));
	if (c->path)
		g_hash_table_insert(al, "object", g_strdup(c->path));

	return al;
}