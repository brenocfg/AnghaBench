#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct directory {unsigned int mode; int stage; TYPE_1__ oid; int /*<<< orphan*/  path; int /*<<< orphan*/  len; scalar_t__ baselen; struct directory* up; } ;
struct archiver_context {struct directory* bottom; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  st_add (int,size_t) ; 
 size_t st_add4 (scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct directory* xmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsnprintf (int /*<<< orphan*/ ,size_t,char*,int,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void queue_directory(const unsigned char *sha1,
		struct strbuf *base, const char *filename,
		unsigned mode, int stage, struct archiver_context *c)
{
	struct directory *d;
	size_t len = st_add4(base->len, 1, strlen(filename), 1);
	d = xmalloc(st_add(sizeof(*d), len));
	d->up	   = c->bottom;
	d->baselen = base->len;
	d->mode	   = mode;
	d->stage   = stage;
	c->bottom  = d;
	d->len = xsnprintf(d->path, len, "%.*s%s/", (int)base->len, base->buf, filename);
	hashcpy(d->oid.hash, sha1);
}