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
struct TYPE_2__ {char* TestFile; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_TEST (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ Unity ; 
 int /*<<< orphan*/  UnityBegin () ; 
 int UnityEnd () ; 
 int /*<<< orphan*/  test_custom ; 
 int /*<<< orphan*/  test_custom25 ; 
 int /*<<< orphan*/  test_main ; 

int main(void)
{
  Unity.TestFile = "../ut-2803.c";
  UnityBegin();
  RUN_TEST(test_main, 29);
  RUN_TEST(test_custom, 34);
  RUN_TEST(test_custom25, 43);

  return (UnityEnd());
}