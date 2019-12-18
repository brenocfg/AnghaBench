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
struct archive_write_disk {int /*<<< orphan*/  name; int /*<<< orphan*/  fd; int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int EXT2_APPEND_FL ; 
 int EXT2_IMMUTABLE_FL ; 
 int SF_APPEND ; 
 int SF_IMMUTABLE ; 
 int UF_APPEND ; 
 int UF_IMMUTABLE ; 
 int /*<<< orphan*/  archive_entry_mode (int /*<<< orphan*/ ) ; 
 int set_fflags_platform (struct archive_write_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int
clear_nochange_fflags(struct archive_write_disk *a)
{
	mode_t		mode = archive_entry_mode(a->entry);
	const int nochange_flags = 0
#ifdef SF_IMMUTABLE
	    | SF_IMMUTABLE
#endif
#ifdef UF_IMMUTABLE
	    | UF_IMMUTABLE
#endif
#ifdef SF_APPEND
	    | SF_APPEND
#endif
#ifdef UF_APPEND
	    | UF_APPEND
#endif
#ifdef EXT2_APPEND_FL
	    | EXT2_APPEND_FL
#endif
#ifdef EXT2_IMMUTABLE_FL
	    | EXT2_IMMUTABLE_FL
#endif
	;

	return (set_fflags_platform(a, a->fd, a->name, mode, 0,
	    nochange_flags));
}