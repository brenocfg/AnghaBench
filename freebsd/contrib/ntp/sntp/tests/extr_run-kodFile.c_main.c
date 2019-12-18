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
 int /*<<< orphan*/  test_ReadCorrectFile ; 
 int /*<<< orphan*/  test_ReadEmptyFile ; 
 int /*<<< orphan*/  test_ReadFileWithBlankLines ; 
 int /*<<< orphan*/  test_WriteEmptyFile ; 
 int /*<<< orphan*/  test_WriteFileWithMultipleEntries ; 
 int /*<<< orphan*/  test_WriteFileWithSingleEntry ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("kodFile.c");
  RUN_TEST(test_ReadEmptyFile, 19);
  RUN_TEST(test_ReadCorrectFile, 20);
  RUN_TEST(test_ReadFileWithBlankLines, 21);
  RUN_TEST(test_WriteEmptyFile, 22);
  RUN_TEST(test_WriteFileWithSingleEntry, 23);
  RUN_TEST(test_WriteFileWithMultipleEntries, 24);

  return (UnityEnd());
}