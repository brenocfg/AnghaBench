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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ __flbf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xo_is_line_buffered (FILE *stream)
{
#if HAVE___FLBF
    if (__flbf(stream))
	return 1;
#else /* HAVE___FLBF */
    if (isatty(fileno(stream)))
	return 1;
#endif /* HAVE___FLBF */
    return 0;
}