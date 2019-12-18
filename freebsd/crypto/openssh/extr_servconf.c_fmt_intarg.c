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
typedef  int ServerOpCodes ;

/* Variables and functions */
 char const* fmt_multistate_int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multistate_addressfamily ; 
 int /*<<< orphan*/  multistate_compression ; 
 int /*<<< orphan*/  multistate_gatewayports ; 
 int /*<<< orphan*/  multistate_permitrootlogin ; 
 int /*<<< orphan*/  multistate_tcpfwd ; 
#define  sAddressFamily 134 
#define  sAllowStreamLocalForwarding 133 
#define  sAllowTcpForwarding 132 
#define  sCompression 131 
#define  sFingerprintHash 130 
#define  sGatewayPorts 129 
#define  sPermitRootLogin 128 
 char const* ssh_digest_alg_name (int) ; 

__attribute__((used)) static const char *
fmt_intarg(ServerOpCodes code, int val)
{
	if (val == -1)
		return "unset";
	switch (code) {
	case sAddressFamily:
		return fmt_multistate_int(val, multistate_addressfamily);
	case sPermitRootLogin:
		return fmt_multistate_int(val, multistate_permitrootlogin);
	case sGatewayPorts:
		return fmt_multistate_int(val, multistate_gatewayports);
	case sCompression:
		return fmt_multistate_int(val, multistate_compression);
	case sAllowTcpForwarding:
		return fmt_multistate_int(val, multistate_tcpfwd);
	case sAllowStreamLocalForwarding:
		return fmt_multistate_int(val, multistate_tcpfwd);
	case sFingerprintHash:
		return ssh_digest_alg_name(val);
	default:
		switch (val) {
		case 0:
			return "no";
		case 1:
			return "yes";
		default:
			return "UNKNOWN";
		}
	}
}