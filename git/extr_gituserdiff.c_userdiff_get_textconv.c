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
struct userdiff_driver {struct notes_cache* textconv_cache; int /*<<< orphan*/  textconv; int /*<<< orphan*/  name; scalar_t__ textconv_want_cache; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct notes_cache {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  notes_cache_init (struct repository*,struct notes_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct notes_cache* xmalloc (int) ; 

struct userdiff_driver *userdiff_get_textconv(struct repository *r,
					      struct userdiff_driver *driver)
{
	if (!driver->textconv)
		return NULL;

	if (driver->textconv_want_cache && !driver->textconv_cache) {
		struct notes_cache *c = xmalloc(sizeof(*c));
		struct strbuf name = STRBUF_INIT;

		strbuf_addf(&name, "textconv/%s", driver->name);
		notes_cache_init(r, c, name.buf, driver->textconv);
		driver->textconv_cache = c;
		strbuf_release(&name);
	}

	return driver;
}