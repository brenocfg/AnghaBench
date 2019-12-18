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
typedef  int nlm4_stats ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EDEADLK ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOLCK ; 
 int EROFS ; 
 int ESTALE ; 
#define  nlm4_deadlck 135 
#define  nlm4_denied 134 
#define  nlm4_denied_nolocks 133 
#define  nlm4_failed 132 
#define  nlm4_fbig 131 
#define  nlm4_granted 130 
#define  nlm4_rofs 129 
#define  nlm4_stale_fh 128 

__attribute__((used)) static int
nlm_map_status(nlm4_stats stat)
{
	switch (stat) {
	case nlm4_granted:
		return (0);

	case nlm4_denied:
		return (EAGAIN);

	case nlm4_denied_nolocks:
		return (ENOLCK);

	case nlm4_deadlck:
		return (EDEADLK);

	case nlm4_rofs:
		return (EROFS);

	case nlm4_stale_fh:
		return (ESTALE);

	case nlm4_fbig:
		return (EFBIG);

	case nlm4_failed:
		return (EACCES);

	default:
		return (EINVAL);
	}
}