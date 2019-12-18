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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
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
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ps_pwrite (struct ps_prochandle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
thr_pwrite(struct ps_prochandle *ph, psaddr_t addr, uint64_t val,
    u_int size, u_int byteorder)
{
	uint8_t buf[sizeof(val)];
	ps_err_e err;

	if (size > sizeof(buf))
		return (EOVERFLOW);

	switch (byteorder) {
	case BIG_ENDIAN:
		switch (size) {
		case 1:
			buf[0] = (uint8_t)val;
			break;
		case 2:
			be16enc(buf, (uint16_t)val);
			break;
		case 4:
			be32enc(buf, (uint32_t)val);
			break;
		case 8:
			be64enc(buf, (uint64_t)val);
			break;
		default:
			return (EINVAL);
		}
		break;
	case LITTLE_ENDIAN:
		switch (size) {
		case 1:
			buf[0] = (uint8_t)val;
			break;
		case 2:
			le16enc(buf, (uint16_t)val);
			break;
		case 4:
			le32enc(buf, (uint32_t)val);
			break;
		case 8:
			le64enc(buf, (uint64_t)val);
			break;
		default:
			return (EINVAL);
		}
		break;
	default:
		return (EINVAL);
	}

	err = ps_pwrite(ph, addr, buf, size);
	return ((err != PS_OK) ? EFAULT : 0);
}