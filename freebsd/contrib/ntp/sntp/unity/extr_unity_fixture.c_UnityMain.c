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
struct TYPE_2__ {unsigned int RepeatCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 
 int /*<<< orphan*/  UnityBegin (char const*) ; 
 int /*<<< orphan*/  UnityEnd () ; 
 int UnityFailureCount () ; 
 TYPE_1__ UnityFixture ; 
 int UnityGetCommandLineOptions (int,char const**) ; 
 int /*<<< orphan*/  announceTestRun (unsigned int) ; 

int UnityMain(int argc, const char* argv[], void (*runAllTests)(void))
{
    int result = UnityGetCommandLineOptions(argc, argv);
    unsigned int r;
    if (result != 0)
        return result;

    for (r = 0; r < UnityFixture.RepeatCount; r++)
    {
        UnityBegin(argv[0]);
        announceTestRun(r);
        runAllTests();
        UNITY_OUTPUT_CHAR('\n');
        UnityEnd();
    }

    return UnityFailureCount();
}