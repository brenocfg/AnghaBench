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
struct tempfile {int dummy; } ;

/* Variables and functions */
 struct tempfile* xmks_tempfile_m (char const*,int) ; 

__attribute__((used)) static inline struct tempfile *xmks_tempfile(const char *filename_template)
{
	return xmks_tempfile_m(filename_template, 0600);
}