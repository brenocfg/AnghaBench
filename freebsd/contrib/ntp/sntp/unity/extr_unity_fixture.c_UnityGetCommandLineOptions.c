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
struct TYPE_2__ {int Verbose; char const* GroupFilter; char const* NameFilter; int RepeatCount; } ;

/* Variables and functions */
 TYPE_1__ UnityFixture ; 
 int atoi (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int UnityGetCommandLineOptions(int argc, const char* argv[])
{
    int i;
    UnityFixture.Verbose = 0;
    UnityFixture.GroupFilter = 0;
    UnityFixture.NameFilter = 0;
    UnityFixture.RepeatCount = 1;

    if (argc == 1)
        return 0;

    for (i = 1; i < argc; )
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            UnityFixture.Verbose = 1;
            i++;
        }
        else if (strcmp(argv[i], "-g") == 0)
        {
            i++;
            if (i >= argc)
                return 1;
            UnityFixture.GroupFilter = argv[i];
            i++;
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            i++;
            if (i >= argc)
                return 1;
            UnityFixture.NameFilter = argv[i];
            i++;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            UnityFixture.RepeatCount = 2;
            i++;
            if (i < argc)
            {
                if (*(argv[i]) >= '0' && *(argv[i]) <= '9')
                {
                    UnityFixture.RepeatCount = atoi(argv[i]);
                    i++;
                }
            }
        } else {
            // ignore unknown parameter
            i++;
        }
    }
    return 0;
}