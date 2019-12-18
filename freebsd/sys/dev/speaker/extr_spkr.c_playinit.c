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
 int /*<<< orphan*/  DFLT_OCTAVE ; 
 int DFLT_TEMPO ; 
 int /*<<< orphan*/  DFLT_VALUE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NORMAL ; 
 int SECS_PER_MIN ; 
 int /*<<< orphan*/  TRUE ; 
 int WHOLE_NOTE ; 
 int /*<<< orphan*/  fill ; 
 int /*<<< orphan*/  octave ; 
 int /*<<< orphan*/  octprefix ; 
 int /*<<< orphan*/  octtrack ; 
 int /*<<< orphan*/  value ; 
 int whole ; 

__attribute__((used)) static void
playinit()
{
    octave = DFLT_OCTAVE;
    whole = (100 * SECS_PER_MIN * WHOLE_NOTE) / DFLT_TEMPO;
    fill = NORMAL;
    value = DFLT_VALUE;
    octtrack = FALSE;
    octprefix = TRUE;	/* act as though there was an initial O(n) */
}