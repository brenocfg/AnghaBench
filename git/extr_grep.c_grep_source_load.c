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
struct grep_source {int type; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  GREP_SOURCE_BUF 130 
#define  GREP_SOURCE_FILE 129 
#define  GREP_SOURCE_OID 128 
 int grep_source_load_file (struct grep_source*) ; 
 int grep_source_load_oid (struct grep_source*) ; 

__attribute__((used)) static int grep_source_load(struct grep_source *gs)
{
	if (gs->buf)
		return 0;

	switch (gs->type) {
	case GREP_SOURCE_FILE:
		return grep_source_load_file(gs);
	case GREP_SOURCE_OID:
		return grep_source_load_oid(gs);
	case GREP_SOURCE_BUF:
		return gs->buf ? 0 : -1;
	}
	BUG("invalid grep_source type to load");
}