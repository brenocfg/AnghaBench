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
struct field {int /*<<< orphan*/  kernel; scalar_t__ field; } ;
typedef  int /*<<< orphan*/  jsmntok_t ;

/* Variables and functions */
 int /*<<< orphan*/  addfield (char*,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cut_comma (char*,int /*<<< orphan*/ *) ; 
 struct field* fields ; 
 scalar_t__ json_streq (char*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int match_field(char *map, jsmntok_t *field, int nz,
		       char **event, jsmntok_t *val)
{
	struct field *f;
	jsmntok_t newval = *val;

	for (f = fields; f->field; f++)
		if (json_streq(map, field, f->field) && nz) {
			cut_comma(map, &newval);
			addfield(map, event, ",", f->kernel, &newval);
			return 1;
		}
	return 0;
}