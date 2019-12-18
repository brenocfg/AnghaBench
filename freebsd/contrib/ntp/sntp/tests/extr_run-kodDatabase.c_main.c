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

/* Variables and functions */
 int /*<<< orphan*/  RUN_TEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnityBegin (char*) ; 
 int UnityEnd () ; 
 char* progname ; 
 int /*<<< orphan*/  suite_setup () ; 
 int /*<<< orphan*/  test_AddDuplicate ; 
 int /*<<< orphan*/  test_DeleteEntry ; 
 int /*<<< orphan*/  test_MultipleEntryHandling ; 
 int /*<<< orphan*/  test_NoMatchInSearch ; 
 int /*<<< orphan*/  test_SingleEntryHandling ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("kodDatabase.c");
  RUN_TEST(test_SingleEntryHandling, 14);
  RUN_TEST(test_MultipleEntryHandling, 15);
  RUN_TEST(test_NoMatchInSearch, 16);
  RUN_TEST(test_AddDuplicate, 17);
  RUN_TEST(test_DeleteEntry, 18);

  return (UnityEnd());
}