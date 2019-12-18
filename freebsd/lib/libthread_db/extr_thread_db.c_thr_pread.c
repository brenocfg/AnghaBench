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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_int ;
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  psaddr_t ;
typedef  scalar_t__ ps_err_e ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  BIG_ENDIAN 129 
 int EFAULT ; 
 int EINVAL ; 
 int EOVERFLOW ; 
#define  LITTLE_ENDIAN 128 
 scalar_t__ PS_OK ; 
 int /*<<< orphan*/  be16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64dec (int /*<<< orphan*/ *) ; 
 scalar_t__ ps_pread (struct ps_prochandle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
thr_pread(struct ps_prochandle *ph, psaddr_t addr, uint64_t *val,
    u_int size, u_int byteorder)
{
	uint8_t buf[sizeof(*val)];
	ps_err_e err;

	if (size > sizeof(buf))
		return (EOVERFLOW);

	err = ps_pread(ph, addr, buf, size);
	if (err != PS_OK)
		return (EFAULT);

	switch (byteorder) {
	case BIG_ENDIAN:
		switch (size) {
		case 1:
			*val = buf[0];
			break;
		case 2:
			*val = be16dec(buf);
			break;
		case 4:
			*val = be32dec(buf);
			break;
		case 8:
			*val = be64dec(buf);
			break;
		default:
			return (EINVAL);
		}
		break;
	case LITTLE_ENDIAN:
		switch (size) {
		case 1:
			*val = buf[0];
			break;
		case 2:
			*val = le16dec(buf);
			break;
		case 4:
			*val = le32dec(buf);
			break;
		case 8:
			*val = le64dec(buf);
			break;
		default:
			return (EINVAL);
		}
		break;
	default:
		return (EINVAL);
	}

	return (0);
}