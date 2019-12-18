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

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int ECONNABORTED ; 
 int ECONNREFUSED ; 
 int ECONNRESET ; 
 int EEXIST ; 
 int EHOSTDOWN ; 
 int EINVAL ; 
 int EIO ; 
 int EMLINK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int
ng_btsocket_l2cap_result2errno(int result)
{
	switch (result) {
	case 0x00: /* No error */ 
		return (0);

	case 0x01: /* Unknown HCI command */
		return (ENODEV);

	case 0x02: /* No connection */
		return (ENOTCONN);

	case 0x03: /* Hardware failure */
		return (EIO);

	case 0x04: /* Page timeout */
		return (EHOSTDOWN);

	case 0x05: /* Authentication failure */
	case 0x06: /* Key missing */
	case 0x18: /* Pairing not allowed */
	case 0x21: /* Role change not allowed */
	case 0x24: /* LMP PSU not allowed */
	case 0x25: /* Encryption mode not acceptable */
	case 0x26: /* Unit key used */
		return (EACCES);

	case 0x07: /* Memory full */
		return (ENOMEM);

	case 0x08:   /* Connection timeout */
	case 0x10:   /* Host timeout */
	case 0x22:   /* LMP response timeout */
	case 0xee:   /* HCI timeout */
	case 0xeeee: /* L2CAP timeout */
		return (ETIMEDOUT);

	case 0x09: /* Max number of connections */
	case 0x0a: /* Max number of SCO connections to a unit */
		return (EMLINK);

	case 0x0b: /* ACL connection already exists */
		return (EEXIST);

	case 0x0c: /* Command disallowed */
		return (EBUSY);

	case 0x0d: /* Host rejected due to limited resources */
	case 0x0e: /* Host rejected due to securiity reasons */
	case 0x0f: /* Host rejected due to remote unit is a personal unit */
	case 0x1b: /* SCO offset rejected */
	case 0x1c: /* SCO interval rejected */
	case 0x1d: /* SCO air mode rejected */
		return (ECONNREFUSED);

	case 0x11: /* Unsupported feature or parameter value */
	case 0x19: /* Unknown LMP PDU */
	case 0x1a: /* Unsupported remote feature */
	case 0x20: /* Unsupported LMP parameter value */
	case 0x27: /* QoS is not supported */
	case 0x29: /* Paring with unit key not supported */
		return (EOPNOTSUPP);

	case 0x12: /* Invalid HCI command parameter */
	case 0x1e: /* Invalid LMP parameters */
		return (EINVAL);

	case 0x13: /* Other end terminated connection: User ended connection */
	case 0x14: /* Other end terminated connection: Low resources */
	case 0x15: /* Other end terminated connection: About to power off */
		return (ECONNRESET);

	case 0x16: /* Connection terminated by local host */
		return (ECONNABORTED);

#if 0 /* XXX not yet */
	case 0x17: /* Repeated attempts */
	case 0x1f: /* Unspecified error */
	case 0x23: /* LMP error transaction collision */
	case 0x28: /* Instant passed */
#endif
	}

	return (ENOSYS);
}