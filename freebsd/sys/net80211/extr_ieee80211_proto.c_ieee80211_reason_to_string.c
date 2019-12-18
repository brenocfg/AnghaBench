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
typedef  int uint16_t ;

/* Variables and functions */
#define  IEEE80211_REASON_4WAY_HANDSHAKE_TIMEOUT 173 
#define  IEEE80211_REASON_802_1X_AUTH_FAILED 172 
#define  IEEE80211_REASON_AKMP_INVALID 171 
#define  IEEE80211_REASON_ASSOC_EXPIRE 170 
#define  IEEE80211_REASON_ASSOC_LEAVE 169 
#define  IEEE80211_REASON_ASSOC_NOT_AUTHED 168 
#define  IEEE80211_REASON_ASSOC_TOOMANY 167 
#define  IEEE80211_REASON_AUTH_EXPIRE 166 
#define  IEEE80211_REASON_AUTH_LEAVE 165 
#define  IEEE80211_REASON_BAD_MECHANISM 164 
#define  IEEE80211_REASON_CIPHER_SUITE_REJECTED 163 
#define  IEEE80211_REASON_DISASSOC_PWRCAP_BAD 162 
#define  IEEE80211_REASON_DISASSOC_SUPCHAN_BAD 161 
#define  IEEE80211_REASON_GROUP_CIPHER_INVALID 160 
#define  IEEE80211_REASON_GROUP_KEY_UPDATE_TIMEOUT 159 
#define  IEEE80211_REASON_IE_INVALID 158 
#define  IEEE80211_REASON_IE_IN_4WAY_DIFFERS 157 
#define  IEEE80211_REASON_INSUFFICIENT_BW 156 
#define  IEEE80211_REASON_INVALID_RSN_IE_CAP 155 
#define  IEEE80211_REASON_LEAVING_QBSS 154 
#define  IEEE80211_REASON_MESH_CHAN_SWITCH_REG 153 
#define  IEEE80211_REASON_MESH_CHAN_SWITCH_UNSPEC 152 
#define  IEEE80211_REASON_MESH_CLOSE_RCVD 151 
#define  IEEE80211_REASON_MESH_CONFIRM_TIMEOUT 150 
#define  IEEE80211_REASON_MESH_CPVIOLATION 149 
#define  IEEE80211_REASON_MESH_INCONS_PARAMS 148 
#define  IEEE80211_REASON_MESH_INVALID_GTK 147 
#define  IEEE80211_REASON_MESH_INVALID_SECURITY 146 
#define  IEEE80211_REASON_MESH_MAC_ALRDY_EXISTS_MBSS 145 
#define  IEEE80211_REASON_MESH_MAX_PEERS 144 
#define  IEEE80211_REASON_MESH_MAX_RETRIES 143 
#define  IEEE80211_REASON_MESH_PERR_DEST_UNREACH 142 
#define  IEEE80211_REASON_MESH_PERR_NO_FI 141 
#define  IEEE80211_REASON_MESH_PERR_NO_PROXY 140 
#define  IEEE80211_REASON_MIC_FAILURE 139 
#define  IEEE80211_REASON_NOT_ASSOCED 138 
#define  IEEE80211_REASON_NOT_AUTHED 137 
#define  IEEE80211_REASON_OUTSIDE_TXOP 136 
#define  IEEE80211_REASON_PAIRWISE_CIPHER_INVALID 135 
#define  IEEE80211_REASON_PEER_LINK_CANCELED 134 
#define  IEEE80211_REASON_SETUP_NEEDED 133 
#define  IEEE80211_REASON_TIMEOUT 132 
#define  IEEE80211_REASON_TOOMANY_FRAMES 131 
#define  IEEE80211_REASON_UNSPECIFIED 130 
#define  IEEE80211_REASON_UNSPECIFIED_QOS 129 
#define  IEEE80211_REASON_UNSUPP_RSN_IE_VERSION 128 

const char *
ieee80211_reason_to_string(uint16_t reason)
{
	switch (reason) {
	case IEEE80211_REASON_UNSPECIFIED:
		return ("unspecified");
	case IEEE80211_REASON_AUTH_EXPIRE:
		return ("previous authentication is expired");
	case IEEE80211_REASON_AUTH_LEAVE:
		return ("sending STA is leaving/has left IBSS or ESS");
	case IEEE80211_REASON_ASSOC_EXPIRE:
		return ("disassociated due to inactivity");
	case IEEE80211_REASON_ASSOC_TOOMANY:
		return ("too many associated STAs");
	case IEEE80211_REASON_NOT_AUTHED:
		return ("class 2 frame received from nonauthenticated STA");
	case IEEE80211_REASON_NOT_ASSOCED:
		return ("class 3 frame received from nonassociated STA");
	case IEEE80211_REASON_ASSOC_LEAVE:
		return ("sending STA is leaving/has left BSS");
	case IEEE80211_REASON_ASSOC_NOT_AUTHED:
		return ("STA requesting (re)association is not authenticated");
	case IEEE80211_REASON_DISASSOC_PWRCAP_BAD:
		return ("information in the Power Capability element is "
			"unacceptable");
	case IEEE80211_REASON_DISASSOC_SUPCHAN_BAD:
		return ("information in the Supported Channels element is "
			"unacceptable");
	case IEEE80211_REASON_IE_INVALID:
		return ("invalid element");
	case IEEE80211_REASON_MIC_FAILURE:
		return ("MIC failure");
	case IEEE80211_REASON_4WAY_HANDSHAKE_TIMEOUT:
		return ("4-Way handshake timeout");
	case IEEE80211_REASON_GROUP_KEY_UPDATE_TIMEOUT:
		return ("group key update timeout");
	case IEEE80211_REASON_IE_IN_4WAY_DIFFERS:
		return ("element in 4-Way handshake different from "
			"(re)association request/probe response/beacon frame");
	case IEEE80211_REASON_GROUP_CIPHER_INVALID:
		return ("invalid group cipher");
	case IEEE80211_REASON_PAIRWISE_CIPHER_INVALID:
		return ("invalid pairwise cipher");
	case IEEE80211_REASON_AKMP_INVALID:
		return ("invalid AKMP");
	case IEEE80211_REASON_UNSUPP_RSN_IE_VERSION:
		return ("unsupported version in RSN IE");
	case IEEE80211_REASON_INVALID_RSN_IE_CAP:
		return ("invalid capabilities in RSN IE");
	case IEEE80211_REASON_802_1X_AUTH_FAILED:
		return ("IEEE 802.1X authentication failed");
	case IEEE80211_REASON_CIPHER_SUITE_REJECTED:
		return ("cipher suite rejected because of the security "
			"policy");
	case IEEE80211_REASON_UNSPECIFIED_QOS:
		return ("unspecified (QoS-related)");
	case IEEE80211_REASON_INSUFFICIENT_BW:
		return ("QoS AP lacks sufficient bandwidth for this QoS STA");
	case IEEE80211_REASON_TOOMANY_FRAMES:
		return ("too many frames need to be acknowledged");
	case IEEE80211_REASON_OUTSIDE_TXOP:
		return ("STA is transmitting outside the limits of its TXOPs");
	case IEEE80211_REASON_LEAVING_QBSS:
		return ("requested from peer STA (the STA is "
			"resetting/leaving the BSS)");
	case IEEE80211_REASON_BAD_MECHANISM:
		return ("requested from peer STA (it does not want to use "
			"the mechanism)");
	case IEEE80211_REASON_SETUP_NEEDED:
		return ("requested from peer STA (setup is required for the "
			"used mechanism)");
	case IEEE80211_REASON_TIMEOUT:
		return ("requested from peer STA (timeout)");
	case IEEE80211_REASON_PEER_LINK_CANCELED:
		return ("SME cancels the mesh peering instance (not related "
			"to the maximum number of peer mesh STAs)");
	case IEEE80211_REASON_MESH_MAX_PEERS:
		return ("maximum number of peer mesh STAs was reached");
	case IEEE80211_REASON_MESH_CPVIOLATION:
		return ("the received information violates the Mesh "
			"Configuration policy configured in the mesh STA "
			"profile");
	case IEEE80211_REASON_MESH_CLOSE_RCVD:
		return ("the mesh STA has received a Mesh Peering Close "
			"message requesting to close the mesh peering");
	case IEEE80211_REASON_MESH_MAX_RETRIES:
		return ("the mesh STA has resent dot11MeshMaxRetries Mesh "
			"Peering Open messages, without receiving a Mesh "
			"Peering Confirm message");
	case IEEE80211_REASON_MESH_CONFIRM_TIMEOUT:
		return ("the confirmTimer for the mesh peering instance times "
			"out");
	case IEEE80211_REASON_MESH_INVALID_GTK:
		return ("the mesh STA fails to unwrap the GTK or the values "
			"in the wrapped contents do not match");
	case IEEE80211_REASON_MESH_INCONS_PARAMS:
		return ("the mesh STA receives inconsistent information about "
			"the mesh parameters between Mesh Peering Management "
			"frames");
	case IEEE80211_REASON_MESH_INVALID_SECURITY:
		return ("the mesh STA fails the authenticated mesh peering "
			"exchange because due to failure in selecting "
			"pairwise/group ciphersuite");
	case IEEE80211_REASON_MESH_PERR_NO_PROXY:
		return ("the mesh STA does not have proxy information for "
			"this external destination");
	case IEEE80211_REASON_MESH_PERR_NO_FI:
		return ("the mesh STA does not have forwarding information "
			"for this destination");
	case IEEE80211_REASON_MESH_PERR_DEST_UNREACH:
		return ("the mesh STA determines that the link to the next "
			"hop of an active path in its forwarding information "
			"is no longer usable");
	case IEEE80211_REASON_MESH_MAC_ALRDY_EXISTS_MBSS:
		return ("the MAC address of the STA already exists in the "
			"mesh BSS");
	case IEEE80211_REASON_MESH_CHAN_SWITCH_REG:
		return ("the mesh STA performs channel switch to meet "
			"regulatory requirements");
	case IEEE80211_REASON_MESH_CHAN_SWITCH_UNSPEC:
		return ("the mesh STA performs channel switch with "
			"unspecified reason");
	default:
		return ("reserved/unknown");
	}
}