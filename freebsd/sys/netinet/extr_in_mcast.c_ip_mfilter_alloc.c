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
struct in_mfilter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INMFILTER ; 
 int /*<<< orphan*/  imf_init (struct in_mfilter*,int const,int const) ; 
 struct in_mfilter* malloc (int,int /*<<< orphan*/ ,int const) ; 

struct in_mfilter *
ip_mfilter_alloc(const int mflags, const int st0, const int st1)
{
	struct in_mfilter *imf;

	imf = malloc(sizeof(*imf), M_INMFILTER, mflags);
	if (imf != NULL)
		imf_init(imf, st0, st1);

	return (imf);
}