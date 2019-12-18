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
struct string_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_person_from_buf (int,struct string_list*,char const*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

__attribute__((used)) static void record_person(int which, struct string_list *people,
			  struct commit *commit)
{
	const char *buffer = get_commit_buffer(commit, NULL);
	record_person_from_buf(which, people, buffer);
	unuse_commit_buffer(commit, buffer);
}