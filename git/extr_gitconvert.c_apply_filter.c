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
struct strbuf {int dummy; } ;
struct delayed_checkout {int dummy; } ;
struct convert_driver {char* clean; char* smudge; scalar_t__* process; } ;

/* Variables and functions */
 unsigned int const CAP_CLEAN ; 
 unsigned int const CAP_SMUDGE ; 
 int apply_multi_file_filter (char const*,char const*,size_t,int,struct strbuf*,scalar_t__*,unsigned int const,struct delayed_checkout*) ; 
 int apply_single_file_filter (char const*,char const*,size_t,int,struct strbuf*,char const*) ; 

__attribute__((used)) static int apply_filter(const char *path, const char *src, size_t len,
			int fd, struct strbuf *dst, struct convert_driver *drv,
			const unsigned int wanted_capability,
			struct delayed_checkout *dco)
{
	const char *cmd = NULL;

	if (!drv)
		return 0;

	if (!dst)
		return 1;

	if ((wanted_capability & CAP_CLEAN) && !drv->process && drv->clean)
		cmd = drv->clean;
	else if ((wanted_capability & CAP_SMUDGE) && !drv->process && drv->smudge)
		cmd = drv->smudge;

	if (cmd && *cmd)
		return apply_single_file_filter(path, src, len, fd, dst, cmd);
	else if (drv->process && *drv->process)
		return apply_multi_file_filter(path, src, len, fd, dst,
			drv->process, wanted_capability, dco);

	return 0;
}