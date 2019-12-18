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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  o_mode_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ACE_APPEND_DATA ; 
 int ACE_DELETE_CHILD ; 
 int ACE_EXECUTE ; 
 int ACE_READ_DATA ; 
 int ACE_WRITE_DATA ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  S_IROTH ; 
 int /*<<< orphan*/  S_IWOTH ; 
 int /*<<< orphan*/  S_IXOTH ; 

__attribute__((used)) static int
ace_mask_to_mode(uint32_t  mask, o_mode_t *modep, boolean_t isdir)
{
	int error = 0;
	o_mode_t mode = 0;
	uint32_t bits, wantbits;

	/* read */
	if (mask & ACE_READ_DATA)
		mode |= S_IROTH;

	/* write */
	wantbits = (ACE_WRITE_DATA | ACE_APPEND_DATA);
	if (isdir)
		wantbits |= ACE_DELETE_CHILD;
	bits = mask & wantbits;
	if (bits != 0) {
		if (bits != wantbits) {
			error = ENOTSUP;
			goto out;
		}
		mode |= S_IWOTH;
	}

	/* exec */
	if (mask & ACE_EXECUTE) {
		mode |= S_IXOTH;
	}

	*modep = mode;

out:
	return (error);
}