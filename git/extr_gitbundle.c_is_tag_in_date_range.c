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
typedef  int timestamp_t ;
struct rev_info {int max_age; int min_age; } ;
struct object {int /*<<< orphan*/  oid; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* memchr (char*,char,int) ; 
 char* memmem (char*,unsigned long,char*,int) ; 
 int parse_timestamp (char*,int /*<<< orphan*/ *,int) ; 
 char* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 

__attribute__((used)) static int is_tag_in_date_range(struct object *tag, struct rev_info *revs)
{
	unsigned long size;
	enum object_type type;
	char *buf = NULL, *line, *lineend;
	timestamp_t date;
	int result = 1;

	if (revs->max_age == -1 && revs->min_age == -1)
		goto out;

	buf = read_object_file(&tag->oid, &type, &size);
	if (!buf)
		goto out;
	line = memmem(buf, size, "\ntagger ", 8);
	if (!line++)
		goto out;
	lineend = memchr(line, '\n', buf + size - line);
	line = memchr(line, '>', lineend ? lineend - line : buf + size - line);
	if (!line++)
		goto out;
	date = parse_timestamp(line, NULL, 10);
	result = (revs->max_age == -1 || revs->max_age < date) &&
		(revs->min_age == -1 || revs->min_age > date);
out:
	free(buf);
	return result;
}