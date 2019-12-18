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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int krb5_socklen_t ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int OM_uint32 ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
#define  GSS_C_AF_INET 129 
#define  GSS_C_AF_INET6 128 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ krb5_h_addr2sockaddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sockaddr*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_sockaddr2address (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 

krb5_error_code
_gsskrb5i_address_to_krb5addr(krb5_context context,
			      OM_uint32 gss_addr_type,
			      gss_buffer_desc *gss_addr,
			      int16_t port,
			      krb5_address *address)
{
   int addr_type;
   struct sockaddr sa;
   krb5_socklen_t sa_size = sizeof(sa);
   krb5_error_code problem;

   if (gss_addr == NULL)
      return GSS_S_FAILURE;

   switch (gss_addr_type) {
#ifdef HAVE_IPV6
      case GSS_C_AF_INET6: addr_type = AF_INET6;
                           break;
#endif /* HAVE_IPV6 */

      case GSS_C_AF_INET:  addr_type = AF_INET;
                           break;
      default:
                           return GSS_S_FAILURE;
   }

   problem = krb5_h_addr2sockaddr (context,
				   addr_type,
                                   gss_addr->value,
                                   &sa,
                                   &sa_size,
                                   port);
   if (problem)
      return GSS_S_FAILURE;

   problem = krb5_sockaddr2address (context, &sa, address);

   return problem;
}