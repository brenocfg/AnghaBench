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
struct strbuf {int dummy; } ;
struct config_store_data {int baselen; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static struct strbuf store_create_section(const char *key,
					  const struct config_store_data *store)
{
	const char *dot;
	int i;
	struct strbuf sb = STRBUF_INIT;

	dot = memchr(key, '.', store->baselen);
	if (dot) {
		strbuf_addf(&sb, "[%.*s \"", (int)(dot - key), key);
		for (i = dot - key + 1; i < store->baselen; i++) {
			if (key[i] == '"' || key[i] == '\\')
				strbuf_addch(&sb, '\\');
			strbuf_addch(&sb, key[i]);
		}
		strbuf_addstr(&sb, "\"]\n");
	} else {
		strbuf_addf(&sb, "[%.*s]\n", store->baselen, key);
	}

	return sb;
}