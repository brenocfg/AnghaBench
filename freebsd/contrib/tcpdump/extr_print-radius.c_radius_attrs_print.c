#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct radius_attr {size_t type; int len; } ;
struct TYPE_8__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  (* print_func ) (TYPE_1__*,int /*<<< orphan*/  const*,int,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct radius_attr const) ; 
 size_t TAM_SIZE (TYPE_5__*) ; 
 TYPE_5__* attr_type ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  const*,int,size_t) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
radius_attrs_print(netdissect_options *ndo,
                   register const u_char *attr, u_int length)
{
   register const struct radius_attr *rad_attr = (const struct radius_attr *)attr;
   const char *attr_string;

   while (length > 0)
   {
     if (length < 2)
        goto trunc;
     ND_TCHECK(*rad_attr);

     if (rad_attr->type > 0 && rad_attr->type < TAM_SIZE(attr_type))
	attr_string = attr_type[rad_attr->type].name;
     else
	attr_string = "Unknown";
     if (rad_attr->len < 2)
     {
	ND_PRINT((ndo, "\n\t  %s Attribute (%u), length: %u (bogus, must be >= 2)",
               attr_string,
               rad_attr->type,
               rad_attr->len));
	return;
     }
     if (rad_attr->len > length)
     {
	ND_PRINT((ndo, "\n\t  %s Attribute (%u), length: %u (bogus, goes past end of packet)",
               attr_string,
               rad_attr->type,
               rad_attr->len));
        return;
     }
     ND_PRINT((ndo, "\n\t  %s Attribute (%u), length: %u, Value: ",
            attr_string,
            rad_attr->type,
            rad_attr->len));

     if (rad_attr->type < TAM_SIZE(attr_type))
     {
         if (rad_attr->len > 2)
         {
             if ( attr_type[rad_attr->type].print_func )
                 (*attr_type[rad_attr->type].print_func)(
                     ndo, ((const u_char *)(rad_attr+1)),
                     rad_attr->len - 2, rad_attr->type);
         }
     }
     /* do we also want to see a hex dump ? */
     if (ndo->ndo_vflag> 1)
         print_unknown_data(ndo, (const u_char *)rad_attr+2, "\n\t    ", (rad_attr->len)-2);

     length-=(rad_attr->len);
     rad_attr = (const struct radius_attr *)( ((const char *)(rad_attr))+rad_attr->len);
   }
   return;

trunc:
   ND_PRINT((ndo, "%s", tstr));
}