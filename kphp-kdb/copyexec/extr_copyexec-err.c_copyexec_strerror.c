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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  COPYEXEC_ERR_ALIGN 154 
#define  COPYEXEC_ERR_CHDIR 153 
#define  COPYEXEC_ERR_CRC32 152 
#define  COPYEXEC_ERR_CREAT 151 
#define  COPYEXEC_ERR_DECRYPT 150 
#define  COPYEXEC_ERR_DISCONNECT 149 
#define  COPYEXEC_ERR_FORK 148 
#define  COPYEXEC_ERR_FSTAT 147 
#define  COPYEXEC_ERR_HOSTNAME_MISMATCHED 146 
#define  COPYEXEC_ERR_INVAL 145 
#define  COPYEXEC_ERR_LSEEK 144 
#define  COPYEXEC_ERR_MALLOC 143 
#define  COPYEXEC_ERR_MKDIR 142 
#define  COPYEXEC_ERR_OLD_RESULT 141 
#define  COPYEXEC_ERR_OPEN 140 
#define  COPYEXEC_ERR_PUBKEY_PERMISSIONS 139 
#define  COPYEXEC_ERR_READ 138 
#define  COPYEXEC_ERR_READIN 137 
#define  COPYEXEC_ERR_SHA1 136 
#define  COPYEXEC_ERR_SIZE 135 
#define  COPYEXEC_ERR_STAT 134 
#define  COPYEXEC_ERR_STATUS 133 
#define  COPYEXEC_ERR_ST_DEV 132 
#define  COPYEXEC_ERR_ST_INO 131 
#define  COPYEXEC_ERR_TYPE 130 
#define  COPYEXEC_ERR_UNKNOWN 129 
#define  COPYEXEC_ERR_VOLUME_ID_MISMATCHED 128 
 int /*<<< orphan*/  assert (int) ; 
 int snprintf (char*,int,char*,int) ; 

char *copyexec_strerror (int err) {
  static char buf[64];  switch (err) {
    case COPYEXEC_ERR_LSEEK: return "COPYEXEC_ERR_LSEEK"; break;
    case COPYEXEC_ERR_READ: return "COPYEXEC_ERR_READ"; break;
    case COPYEXEC_ERR_CRC32: return "COPYEXEC_ERR_CRC32"; break;
    case COPYEXEC_ERR_TYPE: return "COPYEXEC_ERR_TYPE"; break;
    case COPYEXEC_ERR_DECRYPT: return "COPYEXEC_ERR_DECRYPT"; break;
    case COPYEXEC_ERR_MALLOC: return "COPYEXEC_ERR_MALLOC"; break;
    case COPYEXEC_ERR_ALIGN: return "COPYEXEC_ERR_ALIGN"; break;
    case COPYEXEC_ERR_SIZE: return "COPYEXEC_ERR_SIZE"; break;
    case COPYEXEC_ERR_SHA1: return "COPYEXEC_ERR_SHA1"; break;
    case COPYEXEC_ERR_MKDIR: return "COPYEXEC_ERR_MKDIR"; break;
    case COPYEXEC_ERR_OPEN: return "COPYEXEC_ERR_OPEN"; break;
    case COPYEXEC_ERR_FSTAT: return "COPYEXEC_ERR_FSTAT"; break;
    case COPYEXEC_ERR_ST_DEV: return "COPYEXEC_ERR_ST_DEV"; break;
    case COPYEXEC_ERR_ST_INO: return "COPYEXEC_ERR_ST_INO"; break;
    case COPYEXEC_ERR_READIN: return "COPYEXEC_ERR_READIN"; break;
    case COPYEXEC_ERR_STATUS: return "COPYEXEC_ERR_STATUS"; break;
    case COPYEXEC_ERR_FORK: return "COPYEXEC_ERR_FORK"; break;
    case COPYEXEC_ERR_CHDIR: return "COPYEXEC_ERR_CHDIR"; break;
    case COPYEXEC_ERR_CREAT: return "COPYEXEC_ERR_CREAT"; break;
    case COPYEXEC_ERR_STAT: return "COPYEXEC_ERR_STAT"; break;
    case COPYEXEC_ERR_PUBKEY_PERMISSIONS: return "COPYEXEC_ERR_PUBKEY_PERMISSIONS"; break;
    case COPYEXEC_ERR_INVAL: return "COPYEXEC_ERR_INVAL"; break;
    case COPYEXEC_ERR_VOLUME_ID_MISMATCHED: return "COPYEXEC_ERR_VOLUME_ID_MISMATCHED"; break;
    case COPYEXEC_ERR_HOSTNAME_MISMATCHED: return "COPYEXEC_ERR_HOSTNAME_MISMATCHED"; break;
    case COPYEXEC_ERR_DISCONNECT: return "COPYEXEC_ERR_DISCONNECT"; break;
    case COPYEXEC_ERR_OLD_RESULT: return "COPYEXEC_ERR_OLD_RESULT"; break;
    case COPYEXEC_ERR_UNKNOWN: return "COPYEXEC_ERR_UNKNOWN"; break;
    default: assert (snprintf (buf, sizeof (buf), "COPYEXEC_ERR_UNKNOWN (%d)", err) < sizeof (buf));
             return buf;
  }
}