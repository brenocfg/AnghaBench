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
struct reflog_walk_info {int dummy; } ;
struct date_mode {int dummy; } ;

/* Variables and functions */
 int format_person_part (struct strbuf*,char,char const*,int /*<<< orphan*/ ,struct date_mode const*) ; 
 char* get_reflog_ident (struct reflog_walk_info*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int format_reflog_person(struct strbuf *sb,
				char part,
				struct reflog_walk_info *log,
				const struct date_mode *dmode)
{
	const char *ident;

	if (!log)
		return 2;

	ident = get_reflog_ident(log);
	if (!ident)
		return 2;

	return format_person_part(sb, part, ident, strlen(ident), dmode);
}