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
typedef  int OpCodes ;

/* Variables and functions */
 char const* fmt_multistate_int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multistate_addressfamily ; 
 int /*<<< orphan*/  multistate_canonicalizehostname ; 
 int /*<<< orphan*/  multistate_controlmaster ; 
 int /*<<< orphan*/  multistate_requesttty ; 
 int /*<<< orphan*/  multistate_strict_hostkey ; 
 int /*<<< orphan*/  multistate_tunnel ; 
 int /*<<< orphan*/  multistate_yesnoask ; 
 int /*<<< orphan*/  multistate_yesnoaskconfirm ; 
#define  oAddKeysToAgent 137 
#define  oAddressFamily 136 
#define  oCanonicalizeHostname 135 
#define  oControlMaster 134 
#define  oFingerprintHash 133 
#define  oRequestTTY 132 
#define  oStrictHostKeyChecking 131 
#define  oTunnel 130 
#define  oUpdateHostkeys 129 
#define  oVerifyHostKeyDNS 128 
 char const* ssh_digest_alg_name (int) ; 

__attribute__((used)) static const char *
fmt_intarg(OpCodes code, int val)
{
	if (val == -1)
		return "unset";
	switch (code) {
	case oAddressFamily:
		return fmt_multistate_int(val, multistate_addressfamily);
	case oVerifyHostKeyDNS:
	case oUpdateHostkeys:
		return fmt_multistate_int(val, multistate_yesnoask);
	case oStrictHostKeyChecking:
		return fmt_multistate_int(val, multistate_strict_hostkey);
	case oControlMaster:
		return fmt_multistate_int(val, multistate_controlmaster);
	case oTunnel:
		return fmt_multistate_int(val, multistate_tunnel);
	case oRequestTTY:
		return fmt_multistate_int(val, multistate_requesttty);
	case oCanonicalizeHostname:
		return fmt_multistate_int(val, multistate_canonicalizehostname);
	case oAddKeysToAgent:
		return fmt_multistate_int(val, multistate_yesnoaskconfirm);
	case oFingerprintHash:
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