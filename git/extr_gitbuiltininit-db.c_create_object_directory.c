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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* get_object_directory () ; 
 int /*<<< orphan*/  safe_create_dir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

__attribute__((used)) static void create_object_directory(void)
{
	struct strbuf path = STRBUF_INIT;
	size_t baselen;

	strbuf_addstr(&path, get_object_directory());
	baselen = path.len;

	safe_create_dir(path.buf, 1);

	strbuf_setlen(&path, baselen);
	strbuf_addstr(&path, "/pack");
	safe_create_dir(path.buf, 1);

	strbuf_setlen(&path, baselen);
	strbuf_addstr(&path, "/info");
	safe_create_dir(path.buf, 1);

	strbuf_release(&path);
}