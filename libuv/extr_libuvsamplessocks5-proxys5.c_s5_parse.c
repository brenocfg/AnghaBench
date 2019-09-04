#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  s5_err ;
struct TYPE_3__ {int state; int arg0; int arg1; int userlen; int* username; int passlen; int* password; int* daddr; int dport; int /*<<< orphan*/  atyp; int /*<<< orphan*/  cmd; int /*<<< orphan*/  methods; } ;
typedef  TYPE_1__ s5_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  S5_AUTH_GSSAPI ; 
 int /*<<< orphan*/  S5_AUTH_NONE ; 
 int /*<<< orphan*/  S5_AUTH_PASSWD ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  s5_atyp_host ; 
 int /*<<< orphan*/  s5_atyp_ipv4 ; 
 int /*<<< orphan*/  s5_atyp_ipv6 ; 
#define  s5_auth_pw_passlen 144 
#define  s5_auth_pw_password 143 
#define  s5_auth_pw_userlen 142 
#define  s5_auth_pw_username 141 
#define  s5_auth_pw_version 140 
 int /*<<< orphan*/  s5_auth_select ; 
 int /*<<< orphan*/  s5_auth_verify ; 
 int /*<<< orphan*/  s5_bad_atyp ; 
 int /*<<< orphan*/  s5_bad_cmd ; 
 int /*<<< orphan*/  s5_bad_version ; 
 int /*<<< orphan*/  s5_cmd_tcp_connect ; 
 int /*<<< orphan*/  s5_cmd_udp_assoc ; 
#define  s5_dead 139 
 int /*<<< orphan*/  s5_exec_cmd ; 
#define  s5_methods 138 
#define  s5_nmethods 137 
 int /*<<< orphan*/  s5_ok ; 
#define  s5_req_atyp 136 
#define  s5_req_atyp_host 135 
#define  s5_req_cmd 134 
#define  s5_req_daddr 133 
#define  s5_req_dport0 132 
#define  s5_req_dport1 131 
#define  s5_req_reserved 130 
#define  s5_req_version 129 
#define  s5_version 128 

s5_err s5_parse(s5_ctx *cx, uint8_t **data, size_t *size) {
  s5_err err;
  uint8_t *p;
  uint8_t c;
  size_t i;
  size_t n;

  p = *data;
  n = *size;
  i = 0;

  while (i < n) {
    c = p[i];
    i += 1;
    switch (cx->state) {
      case s5_version:
        if (c != 5) {
          err = s5_bad_version;
          goto out;
        }
        cx->state = s5_nmethods;
        break;

      case s5_nmethods:
        cx->arg0 = 0;
        cx->arg1 = c;  /* Number of bytes to read. */
        cx->state = s5_methods;
        break;

      case s5_methods:
        if (cx->arg0 < cx->arg1) {
          switch (c) {
            case 0:
              cx->methods |= S5_AUTH_NONE;
              break;
            case 1:
              cx->methods |= S5_AUTH_GSSAPI;
              break;
            case 2:
              cx->methods |= S5_AUTH_PASSWD;
              break;
            /* Ignore everything we don't understand. */
          }
          cx->arg0 += 1;
        }
        if (cx->arg0 == cx->arg1) {
          err = s5_auth_select;
          goto out;
        }
        break;

      case s5_auth_pw_version:
        if (c != 1) {
          err = s5_bad_version;
          goto out;
        }
        cx->state = s5_auth_pw_userlen;
        break;

      case s5_auth_pw_userlen:
        cx->arg0 = 0;
        cx->userlen = c;
        cx->state = s5_auth_pw_username;
        break;

      case s5_auth_pw_username:
        if (cx->arg0 < cx->userlen) {
          cx->username[cx->arg0] = c;
          cx->arg0 += 1;
        }
        if (cx->arg0 == cx->userlen) {
          cx->username[cx->userlen] = '\0';
          cx->state = s5_auth_pw_passlen;
        }
        break;

      case s5_auth_pw_passlen:
        cx->arg0 = 0;
        cx->passlen = c;
        cx->state = s5_auth_pw_password;
        break;

      case s5_auth_pw_password:
        if (cx->arg0 < cx->passlen) {
          cx->password[cx->arg0] = c;
          cx->arg0 += 1;
        }
        if (cx->arg0 == cx->passlen) {
          cx->password[cx->passlen] = '\0';
          cx->state = s5_req_version;
          err = s5_auth_verify;
          goto out;
        }
        break;

      case s5_req_version:
        if (c != 5) {
          err = s5_bad_version;
          goto out;
        }
        cx->state = s5_req_cmd;
        break;

      case s5_req_cmd:
        switch (c) {
          case 1:  /* TCP connect */
            cx->cmd = s5_cmd_tcp_connect;
            break;
          case 3:  /* UDP associate */
            cx->cmd = s5_cmd_udp_assoc;
            break;
          default:
            err = s5_bad_cmd;
            goto out;
        }
        cx->state = s5_req_reserved;
        break;

      case s5_req_reserved:
        cx->state = s5_req_atyp;
        break;

      case s5_req_atyp:
        cx->arg0 = 0;
        switch (c) {
          case 1:  /* IPv4, four octets. */
            cx->state = s5_req_daddr;
            cx->atyp = s5_atyp_ipv4;
            cx->arg1 = 4;
            break;
          case 3:  /* Hostname.  First byte is length. */
            cx->state = s5_req_atyp_host;
            cx->atyp = s5_atyp_host;
            cx->arg1 = 0;
            break;
          case 4:  /* IPv6, sixteen octets. */
            cx->state = s5_req_daddr;
            cx->atyp = s5_atyp_ipv6;
            cx->arg1 = 16;
            break;
          default:
            err = s5_bad_atyp;
            goto out;
        }
        break;

      case s5_req_atyp_host:
        cx->arg1 = c;
        cx->state = s5_req_daddr;
        break;

      case s5_req_daddr:
        if (cx->arg0 < cx->arg1) {
          cx->daddr[cx->arg0] = c;
          cx->arg0 += 1;
        }
        if (cx->arg0 == cx->arg1) {
          cx->daddr[cx->arg1] = '\0';
          cx->state = s5_req_dport0;
        }
        break;

      case s5_req_dport0:
        cx->dport = c << 8;
        cx->state = s5_req_dport1;
        break;

      case s5_req_dport1:
        cx->dport |= c;
        cx->state = s5_dead;
        err = s5_exec_cmd;
        goto out;

      case s5_dead:
        break;

      default:
        abort();
    }
  }
  err = s5_ok;

out:
  *data = p + i;
  *size = n - i;
  return err;
}