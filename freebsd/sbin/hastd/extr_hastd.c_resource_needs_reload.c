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
struct hast_resource {scalar_t__ hr_role; scalar_t__ hr_replication; scalar_t__ hr_checksum; scalar_t__ hr_compression; scalar_t__ hr_timeout; scalar_t__ hr_metaflush; int /*<<< orphan*/  hr_exec; int /*<<< orphan*/  hr_sourceaddr; int /*<<< orphan*/  hr_remoteaddr; int /*<<< orphan*/  hr_localpath; int /*<<< orphan*/  hr_provname; int /*<<< orphan*/  hr_name; } ;

/* Variables and functions */
 scalar_t__ HAST_ROLE_PRIMARY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
resource_needs_reload(const struct hast_resource *res0,
    const struct hast_resource *res1)
{

	PJDLOG_ASSERT(strcmp(res0->hr_name, res1->hr_name) == 0);
	PJDLOG_ASSERT(strcmp(res0->hr_provname, res1->hr_provname) == 0);
	PJDLOG_ASSERT(strcmp(res0->hr_localpath, res1->hr_localpath) == 0);

	if (res0->hr_role != HAST_ROLE_PRIMARY)
		return (false);

	if (strcmp(res0->hr_remoteaddr, res1->hr_remoteaddr) != 0)
		return (true);
	if (strcmp(res0->hr_sourceaddr, res1->hr_sourceaddr) != 0)
		return (true);
	if (res0->hr_replication != res1->hr_replication)
		return (true);
	if (res0->hr_checksum != res1->hr_checksum)
		return (true);
	if (res0->hr_compression != res1->hr_compression)
		return (true);
	if (res0->hr_timeout != res1->hr_timeout)
		return (true);
	if (strcmp(res0->hr_exec, res1->hr_exec) != 0)
		return (true);
	if (res0->hr_metaflush != res1->hr_metaflush)
		return (true);
	return (false);
}