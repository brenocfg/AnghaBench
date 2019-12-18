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
struct ch_mii_data {unsigned int phy_id; unsigned int reg_num; unsigned int val_in; int val_out; } ;

/* Variables and functions */
 unsigned int CHELSIO_GET_MIIREG ; 
 unsigned int CHELSIO_SET_MIIREG ; 
 scalar_t__ doit (char const*,unsigned int,struct ch_mii_data*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ get_int_arg (char*,unsigned int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
mdio_io(int argc, char *argv[], int start_arg, const char *iff_name) 
{ 
        struct ch_mii_data p;
        unsigned int cmd, phy_addr, reg, mmd, val; 
 
        if (argc == start_arg + 3) 
                cmd = CHELSIO_GET_MIIREG; 
        else if (argc == start_arg + 4) 
                cmd = CHELSIO_SET_MIIREG; 
        else 
                return -1; 
 
        if (get_int_arg(argv[start_arg], &phy_addr) || 
            get_int_arg(argv[start_arg + 1], &mmd) || 
            get_int_arg(argv[start_arg + 2], &reg) || 
            (cmd == CHELSIO_SET_MIIREG && get_int_arg(argv[start_arg + 3], &val))) 
                return -1; 

        p.phy_id  = phy_addr | (mmd << 8); 
        p.reg_num = reg; 
        p.val_in  = val; 
 
        if (doit(iff_name, cmd, &p) < 0) 
                err(1, "MDIO %s", cmd == CHELSIO_GET_MIIREG ? "read" : "write");
        if (cmd == CHELSIO_GET_MIIREG) 
                printf("%#x [%u]\n", p.val_out, p.val_out); 
        return 0; 
}