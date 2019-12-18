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
 int /*<<< orphan*/  test_ReadASCIIKeys ; 
 int /*<<< orphan*/  test_ReadEmptyKeyFile ; 
 int /*<<< orphan*/  test_ReadHexKeys ; 
 int /*<<< orphan*/  test_ReadKeyFileWithComments ; 
 int /*<<< orphan*/  test_ReadKeyFileWithInvalidHex ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("keyFile.c");
  RUN_TEST(test_ReadEmptyKeyFile, 12);
  RUN_TEST(test_ReadASCIIKeys, 13);
  RUN_TEST(test_ReadHexKeys, 14);
  RUN_TEST(test_ReadKeyFileWithComments, 15);
  RUN_TEST(test_ReadKeyFileWithInvalidHex, 16);

  return (UnityEnd());
}