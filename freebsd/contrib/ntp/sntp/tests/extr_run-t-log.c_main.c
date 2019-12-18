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
 int /*<<< orphan*/  testChangePrognameInMysyslog ; 
 int /*<<< orphan*/  testOpenLogfileTest ; 
 int /*<<< orphan*/  testWriteInCustomLogfile ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("t-log.c");
  RUN_TEST(testChangePrognameInMysyslog, 10);
  RUN_TEST(testOpenLogfileTest, 11);
  RUN_TEST(testWriteInCustomLogfile, 12);

  return (UnityEnd());
}