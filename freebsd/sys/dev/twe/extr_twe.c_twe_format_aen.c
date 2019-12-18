#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct twe_softc {char* twe_aen_buf; int /*<<< orphan*/ * twe_dev; TYPE_1__* twe_drive; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * td_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_AEN_CODE (int) ; 
 int TWE_AEN_UNIT (int) ; 
 int /*<<< orphan*/  bootverbose ; 
 int device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 char* twe_describe_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_table_aen ; 

__attribute__((used)) static char *
twe_format_aen(struct twe_softc *sc, u_int16_t aen)
{
    device_t	child;
    char	*code, *msg;

    code = twe_describe_code(twe_table_aen, TWE_AEN_CODE(aen));
    msg = code + 2;

    switch (*code) {
    case 'q':
	if (!bootverbose)
	    return(NULL);
	/* FALLTHROUGH */
    case 'a':
	return(msg);

    case 'c':
	if ((child = sc->twe_drive[TWE_AEN_UNIT(aen)].td_disk) != NULL) {
	    snprintf(sc->twe_aen_buf, sizeof(sc->twe_aen_buf), "twed%d: %s",
		device_get_unit(child), msg);
	} else {
	    snprintf(sc->twe_aen_buf, sizeof(sc->twe_aen_buf),
		"twe%d: %s for unknown unit %d", device_get_unit(sc->twe_dev),
		msg, TWE_AEN_UNIT(aen));
	}
	return(sc->twe_aen_buf);

    case 'p':
	snprintf(sc->twe_aen_buf, sizeof(sc->twe_aen_buf),
	    "twe%d: port %d: %s", device_get_unit(sc->twe_dev),
	    TWE_AEN_UNIT(aen), msg);
	return(sc->twe_aen_buf);

	
    case 'x':
    default:
	break;
    }
    snprintf(sc->twe_aen_buf, sizeof(sc->twe_aen_buf), "unknown AEN 0x%x", aen);
    return(sc->twe_aen_buf);
}