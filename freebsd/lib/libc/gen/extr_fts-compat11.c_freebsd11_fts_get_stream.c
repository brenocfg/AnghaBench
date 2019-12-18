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
typedef  int /*<<< orphan*/  FTSENT11 ;
typedef  int /*<<< orphan*/  FTS11 ;

/* Variables and functions */

FTS11 *
(freebsd11_fts_get_stream)(FTSENT11 *p)
{
	return (freebsd11_fts_get_stream(p));
}