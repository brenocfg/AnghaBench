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
struct torus {int flags; TYPE_1__* osm; scalar_t__ debug; int /*<<< orphan*/  z_sz; int /*<<< orphan*/  y_sz; int /*<<< orphan*/  x_sz; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int X_MESH ; 
 int Y_MESH ; 
 int Z_MESH ; 
 int canonicalize (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_tlinks (struct torus*,int,int,int) ; 
 unsigned int fingerprint (struct torus*,int,int,int) ; 
 int handle_case_0x301 (struct torus*,int,int,int) ; 
 int handle_case_0x302 (struct torus*,int,int,int) ; 
 int handle_case_0x303 (struct torus*,int,int,int) ; 
 int handle_case_0x304 (struct torus*,int,int,int) ; 
 int handle_case_0x305 (struct torus*,int,int,int) ; 
 int handle_case_0x308 (struct torus*,int,int,int) ; 
 int handle_case_0x30a (struct torus*,int,int,int) ; 
 int handle_case_0x30c (struct torus*,int,int,int) ; 
 int handle_case_0x501 (struct torus*,int,int,int) ; 
 int handle_case_0x502 (struct torus*,int,int,int) ; 
 int handle_case_0x503 (struct torus*,int,int,int) ; 
 int handle_case_0x510 (struct torus*,int,int,int) ; 
 int handle_case_0x511 (struct torus*,int,int,int) ; 
 int handle_case_0x520 (struct torus*,int,int,int) ; 
 int handle_case_0x522 (struct torus*,int,int,int) ; 
 int handle_case_0x530 (struct torus*,int,int,int) ; 
 int handle_case_0x601 (struct torus*,int,int,int) ; 
 int handle_case_0x604 (struct torus*,int,int,int) ; 
 int handle_case_0x605 (struct torus*,int,int,int) ; 
 int handle_case_0x610 (struct torus*,int,int,int) ; 
 int handle_case_0x611 (struct torus*,int,int,int) ; 
 int handle_case_0x640 (struct torus*,int,int,int) ; 
 int handle_case_0x644 (struct torus*,int,int,int) ; 
 int handle_case_0x650 (struct torus*,int,int,int) ; 
 int handle_case_0x701 (struct torus*,int,int,int) ; 
 int handle_case_0x702 (struct torus*,int,int,int) ; 
 int handle_case_0x703 (struct torus*,int,int,int) ; 
 int handle_case_0x704 (struct torus*,int,int,int) ; 
 int handle_case_0x705 (struct torus*,int,int,int) ; 
 int handle_case_0x707 (struct torus*,int,int,int) ; 
 int handle_case_0x708 (struct torus*,int,int,int) ; 
 int handle_case_0x70a (struct torus*,int,int,int) ; 
 int handle_case_0x70b (struct torus*,int,int,int) ; 
 int handle_case_0x70c (struct torus*,int,int,int) ; 
 int handle_case_0x70d (struct torus*,int,int,int) ; 
 int handle_case_0x70e (struct torus*,int,int,int) ; 
 int handle_case_0x70f (struct torus*,int,int,int) ; 
 int handle_case_0x710 (struct torus*,int,int,int) ; 
 int handle_case_0x711 (struct torus*,int,int,int) ; 
 int handle_case_0x713 (struct torus*,int,int,int) ; 
 int handle_case_0x715 (struct torus*,int,int,int) ; 
 int handle_case_0x717 (struct torus*,int,int,int) ; 
 int handle_case_0x71f (struct torus*,int,int,int) ; 
 int handle_case_0x720 (struct torus*,int,int,int) ; 
 int handle_case_0x722 (struct torus*,int,int,int) ; 
 int handle_case_0x723 (struct torus*,int,int,int) ; 
 int handle_case_0x72a (struct torus*,int,int,int) ; 
 int handle_case_0x72b (struct torus*,int,int,int) ; 
 int handle_case_0x72f (struct torus*,int,int,int) ; 
 int handle_case_0x730 (struct torus*,int,int,int) ; 
 int handle_case_0x731 (struct torus*,int,int,int) ; 
 int handle_case_0x732 (struct torus*,int,int,int) ; 
 int handle_case_0x733 (struct torus*,int,int,int) ; 
 int handle_case_0x737 (struct torus*,int,int,int) ; 
 int handle_case_0x73b (struct torus*,int,int,int) ; 
 int handle_case_0x740 (struct torus*,int,int,int) ; 
 int handle_case_0x744 (struct torus*,int,int,int) ; 
 int handle_case_0x745 (struct torus*,int,int,int) ; 
 int handle_case_0x74c (struct torus*,int,int,int) ; 
 int handle_case_0x74d (struct torus*,int,int,int) ; 
 int handle_case_0x74f (struct torus*,int,int,int) ; 
 int handle_case_0x750 (struct torus*,int,int,int) ; 
 int handle_case_0x751 (struct torus*,int,int,int) ; 
 int handle_case_0x754 (struct torus*,int,int,int) ; 
 int handle_case_0x755 (struct torus*,int,int,int) ; 
 int handle_case_0x757 (struct torus*,int,int,int) ; 
 int handle_case_0x75d (struct torus*,int,int,int) ; 
 int handle_case_0x770 (struct torus*,int,int,int) ; 
 int handle_case_0x771 (struct torus*,int,int,int) ; 
 int handle_case_0x773 (struct torus*,int,int,int) ; 
 int handle_case_0x775 (struct torus*,int,int,int) ; 
 int handle_case_0x780 (struct torus*,int,int,int) ; 
 int handle_case_0x788 (struct torus*,int,int,int) ; 
 int handle_case_0x78a (struct torus*,int,int,int) ; 
 int handle_case_0x78c (struct torus*,int,int,int) ; 
 int handle_case_0x78e (struct torus*,int,int,int) ; 
 int handle_case_0x78f (struct torus*,int,int,int) ; 
 int handle_case_0x7a0 (struct torus*,int,int,int) ; 
 int handle_case_0x7a2 (struct torus*,int,int,int) ; 
 int handle_case_0x7a8 (struct torus*,int,int,int) ; 
 int handle_case_0x7aa (struct torus*,int,int,int) ; 
 int handle_case_0x7ab (struct torus*,int,int,int) ; 
 int handle_case_0x7ae (struct torus*,int,int,int) ; 
 int handle_case_0x7b0 (struct torus*,int,int,int) ; 
 int handle_case_0x7b2 (struct torus*,int,int,int) ; 
 int handle_case_0x7b3 (struct torus*,int,int,int) ; 
 int handle_case_0x7ba (struct torus*,int,int,int) ; 
 int handle_case_0x7c0 (struct torus*,int,int,int) ; 
 int handle_case_0x7c4 (struct torus*,int,int,int) ; 
 int handle_case_0x7c8 (struct torus*,int,int,int) ; 
 int handle_case_0x7cc (struct torus*,int,int,int) ; 
 int handle_case_0x7cd (struct torus*,int,int,int) ; 
 int handle_case_0x7ce (struct torus*,int,int,int) ; 
 int handle_case_0x7d0 (struct torus*,int,int,int) ; 
 int handle_case_0x7d4 (struct torus*,int,int,int) ; 
 int handle_case_0x7d5 (struct torus*,int,int,int) ; 
 int handle_case_0x7dc (struct torus*,int,int,int) ; 
 int handle_case_0x7e0 (struct torus*,int,int,int) ; 
 int handle_case_0x7e8 (struct torus*,int,int,int) ; 
 int handle_case_0x7ea (struct torus*,int,int,int) ; 
 int handle_case_0x7ec (struct torus*,int,int,int) ; 
 int handle_case_0x7f0 (struct torus*,int,int,int) ; 
 int handle_case_0x7f1 (struct torus*,int,int,int) ; 
 int handle_case_0x7f2 (struct torus*,int,int,int) ; 
 int handle_case_0x7f4 (struct torus*,int,int,int) ; 
 int handle_case_0x7f8 (struct torus*,int,int,int) ; 

__attribute__((used)) static
void locate_sw(struct torus *t, int i, int j, int k)
{
	unsigned fp;
	bool success;

	i = canonicalize(i, t->x_sz);
	j = canonicalize(j, t->y_sz);
	k = canonicalize(k, t->z_sz);

	/*
	 * By definition, if a coordinate direction is meshed, we don't
	 * allow it to wrap to zero.
	 */
	if (t->flags & X_MESH) {
		int ip1 = canonicalize(i + 1, t->x_sz);
		if (ip1 < i)
			goto out;
	}
	if (t->flags & Y_MESH) {
		int jp1 = canonicalize(j + 1, t->y_sz);
		if (jp1 < j)
			goto out;
	}
	if (t->flags & Z_MESH) {
		int kp1 = canonicalize(k + 1, t->z_sz);
		if (kp1 < k)
			goto out;
	}
	/*
	 * There are various reasons that the links are not installed between
	 * known torus switches.  These include cases where the search for
	 * new switches only partially succeeds due to missing switches, and
	 * cases where we haven't processed this position yet, but processing
	 * of multiple independent neighbor positions has installed switches
	 * into corners of our case.
	 *
	 * In any event, the topology assumptions made in handling the
	 * fingerprint for this position require that all links be installed
	 * between installed switches for this position.
	 */
again:
	check_tlinks(t, i, j, k);
	fp = fingerprint(t, i, j, k);

	switch (fp) {
	/*
	 * When all switches are present, we are done.  Otherwise, one of
	 * the cases below will be unsuccessful, and we'll be done also.
	 *
	 * Note that check_tlinks() above will ensure all links that are
	 * present are connected, in the event that all our switches are
	 * present due to successful case handling in the surrounding
	 * torus/mesh.
	 */
	case 0x300:
	case 0x500:
	case 0x600:
	case 0x700:
		goto out;
	/*
	 * Ignore the 2D cases where there isn't enough information to uniquely
	 * locate/place a switch into the cube.
	 */
	case 0x30f: 	/* 0 corners available */
	case 0x533: 	/* 0 corners available */
	case 0x655: 	/* 0 corners available */
	case 0x30e:	/* 1 corner available */
	case 0x532:	/* 1 corner available */
	case 0x654:	/* 1 corner available */
	case 0x30d:	/* 1 corner available */
	case 0x531:	/* 1 corner available */
	case 0x651:	/* 1 corner available */
	case 0x30b:	/* 1 corner available */
	case 0x523:	/* 1 corner available */
	case 0x645:	/* 1 corner available */
	case 0x307:	/* 1 corner available */
	case 0x513:	/* 1 corner available */
	case 0x615:	/* 1 corner available */
		goto out;
	/*
	 * Handle the 2D cases with a single existing edge.
	 *
	 */
	case 0x30c:
		success = handle_case_0x30c(t, i, j, k);
		break;
	case 0x303:
		success = handle_case_0x303(t, i, j, k);
		break;
	case 0x305:
		success = handle_case_0x305(t, i, j, k);
		break;
	case 0x30a:
		success = handle_case_0x30a(t, i, j, k);
		break;
	case 0x503:
		success = handle_case_0x503(t, i, j, k);
		break;
	case 0x511:
		success = handle_case_0x511(t, i, j, k);
		break;
	case 0x522:
		success = handle_case_0x522(t, i, j, k);
		break;
	case 0x530:
		success = handle_case_0x530(t, i, j, k);
		break;
	case 0x605:
		success = handle_case_0x605(t, i, j, k);
		break;
	case 0x611:
		success = handle_case_0x611(t, i, j, k);
		break;
	case 0x644:
		success = handle_case_0x644(t, i, j, k);
		break;
	case 0x650:
		success = handle_case_0x650(t, i, j, k);
		break;
	/*
	 * Handle the 2D cases where two existing edges meet at a corner.
	 */
	case 0x301:
		success = handle_case_0x301(t, i, j, k);
		break;
	case 0x302:
		success = handle_case_0x302(t, i, j, k);
		break;
	case 0x304:
		success = handle_case_0x304(t, i, j, k);
		break;
	case 0x308:
		success = handle_case_0x308(t, i, j, k);
		break;
	case 0x501:
		success = handle_case_0x501(t, i, j, k);
		break;
	case 0x502:
		success = handle_case_0x502(t, i, j, k);
		break;
	case 0x520:
		success = handle_case_0x520(t, i, j, k);
		break;
	case 0x510:
		success = handle_case_0x510(t, i, j, k);
		break;
	case 0x601:
		success = handle_case_0x601(t, i, j, k);
		break;
	case 0x604:
		success = handle_case_0x604(t, i, j, k);
		break;
	case 0x610:
		success = handle_case_0x610(t, i, j, k);
		break;
	case 0x640:
		success = handle_case_0x640(t, i, j, k);
		break;
	/*
	 * Ignore the 3D cases where there isn't enough information to uniquely
	 * locate/place a switch into the cube.
	 */
	case 0x7ff:	/* 0 corners available */
	case 0x7fe:	/* 1 corner available */
	case 0x7fd:	/* 1 corner available */
	case 0x7fb:	/* 1 corner available */
	case 0x7f7:	/* 1 corner available */
	case 0x7ef:	/* 1 corner available */
	case 0x7df:	/* 1 corner available */
	case 0x7bf:	/* 1 corner available */
	case 0x77f:	/* 1 corner available */
	case 0x7fc:	/* 2 adj corners available */
	case 0x7fa:	/* 2 adj corners available */
	case 0x7f5:	/* 2 adj corners available */
	case 0x7f3:	/* 2 adj corners available */
	case 0x7cf:	/* 2 adj corners available */
	case 0x7af:	/* 2 adj corners available */
	case 0x75f:	/* 2 adj corners available */
	case 0x73f:	/* 2 adj corners available */
	case 0x7ee:	/* 2 adj corners available */
	case 0x7dd:	/* 2 adj corners available */
	case 0x7bb:	/* 2 adj corners available */
	case 0x777:	/* 2 adj corners available */
		goto out;
	/*
	 * Handle the 3D cases where two existing edges meet at a corner.
	 *
	 */
	case 0x71f:
		success = handle_case_0x71f(t, i, j, k);
		break;
	case 0x72f:
		success = handle_case_0x72f(t, i, j, k);
		break;
	case 0x737:
		success = handle_case_0x737(t, i, j, k);
		break;
	case 0x73b:
		success = handle_case_0x73b(t, i, j, k);
		break;
	case 0x74f:
		success = handle_case_0x74f(t, i, j, k);
		break;
	case 0x757:
		success = handle_case_0x757(t, i, j, k);
		break;
	case 0x75d:
		success = handle_case_0x75d(t, i, j, k);
		break;
	case 0x773:
		success = handle_case_0x773(t, i, j, k);
		break;
	case 0x775:
		success = handle_case_0x775(t, i, j, k);
		break;
	case 0x78f:
		success = handle_case_0x78f(t, i, j, k);
		break;
	case 0x7ab:
		success = handle_case_0x7ab(t, i, j, k);
		break;
	case 0x7ae:
		success = handle_case_0x7ae(t, i, j, k);
		break;
	case 0x7b3:
		success = handle_case_0x7b3(t, i, j, k);
		break;
	case 0x7ba:
		success = handle_case_0x7ba(t, i, j, k);
		break;
	case 0x7cd:
		success = handle_case_0x7cd(t, i, j, k);
		break;
	case 0x7ce:
		success = handle_case_0x7ce(t, i, j, k);
		break;
	case 0x7d5:
		success = handle_case_0x7d5(t, i, j, k);
		break;
	case 0x7dc:
		success = handle_case_0x7dc(t, i, j, k);
		break;
	case 0x7ea:
		success = handle_case_0x7ea(t, i, j, k);
		break;
	case 0x7ec:
		success = handle_case_0x7ec(t, i, j, k);
		break;
	case 0x7f1:
		success = handle_case_0x7f1(t, i, j, k);
		break;
	case 0x7f2:
		success = handle_case_0x7f2(t, i, j, k);
		break;
	case 0x7f4:
		success = handle_case_0x7f4(t, i, j, k);
		break;
	case 0x7f8:
		success = handle_case_0x7f8(t, i, j, k);
		break;
	/*
	 * Handle the cases where three existing edges meet at a corner.
	 *
	 */
	case 0x717:
		success = handle_case_0x717(t, i, j, k);
		break;
	case 0x72b:
		success = handle_case_0x72b(t, i, j, k);
		break;
	case 0x74d:
		success = handle_case_0x74d(t, i, j, k);
		break;
	case 0x771:
		success = handle_case_0x771(t, i, j, k);
		break;
	case 0x78e:
		success = handle_case_0x78e(t, i, j, k);
		break;
	case 0x7b2:
		success = handle_case_0x7b2(t, i, j, k);
		break;
	case 0x7d4:
		success = handle_case_0x7d4(t, i, j, k);
		break;
	case 0x7e8:
		success = handle_case_0x7e8(t, i, j, k);
		break;
	/*
	 * Handle the cases where four corners on a single face are missing.
	 */
	case 0x70f:
		success = handle_case_0x70f(t, i, j, k);
		break;
	case 0x733:
		success = handle_case_0x733(t, i, j, k);
		break;
	case 0x755:
		success = handle_case_0x755(t, i, j, k);
		break;
	case 0x7aa:
		success = handle_case_0x7aa(t, i, j, k);
		break;
	case 0x7cc:
		success = handle_case_0x7cc(t, i, j, k);
		break;
	case 0x7f0:
		success = handle_case_0x7f0(t, i, j, k);
		break;
	/*
	 * Handle the cases where three corners on a single face are missing.
	 */
	case 0x707:
		success = handle_case_0x707(t, i, j, k);
		break;
	case 0x70b:
		success = handle_case_0x70b(t, i, j, k);
		break;
	case 0x70d:
		success = handle_case_0x70d(t, i, j, k);
		break;
	case 0x70e:
		success = handle_case_0x70e(t, i, j, k);
		break;
	case 0x713:
		success = handle_case_0x713(t, i, j, k);
		break;
	case 0x715:
		success = handle_case_0x715(t, i, j, k);
		break;
	case 0x723:
		success = handle_case_0x723(t, i, j, k);
		break;
	case 0x72a:
		success = handle_case_0x72a(t, i, j, k);
		break;
	case 0x731:
		success = handle_case_0x731(t, i, j, k);
		break;
	case 0x732:
		success = handle_case_0x732(t, i, j, k);
		break;
	case 0x745:
		success = handle_case_0x745(t, i, j, k);
		break;
	case 0x74c:
		success = handle_case_0x74c(t, i, j, k);
		break;
	case 0x751:
		success = handle_case_0x751(t, i, j, k);
		break;
	case 0x754:
		success = handle_case_0x754(t, i, j, k);
		break;
	case 0x770:
		success = handle_case_0x770(t, i, j, k);
		break;
	case 0x78a:
		success = handle_case_0x78a(t, i, j, k);
		break;
	case 0x78c:
		success = handle_case_0x78c(t, i, j, k);
		break;
	case 0x7a2:
		success = handle_case_0x7a2(t, i, j, k);
		break;
	case 0x7a8:
		success = handle_case_0x7a8(t, i, j, k);
		break;
	case 0x7b0:
		success = handle_case_0x7b0(t, i, j, k);
		break;
	case 0x7c4:
		success = handle_case_0x7c4(t, i, j, k);
		break;
	case 0x7c8:
		success = handle_case_0x7c8(t, i, j, k);
		break;
	case 0x7d0:
		success = handle_case_0x7d0(t, i, j, k);
		break;
	case 0x7e0:
		success = handle_case_0x7e0(t, i, j, k);
		break;
	/*
	 * Handle the cases where two corners on a single edge are missing.
	 */
	case 0x703:
		success = handle_case_0x703(t, i, j, k);
		break;
	case 0x705:
		success = handle_case_0x705(t, i, j, k);
		break;
	case 0x70a:
		success = handle_case_0x70a(t, i, j, k);
		break;
	case 0x70c:
		success = handle_case_0x70c(t, i, j, k);
		break;
	case 0x711:
		success = handle_case_0x711(t, i, j, k);
		break;
	case 0x722:
		success = handle_case_0x722(t, i, j, k);
		break;
	case 0x730:
		success = handle_case_0x730(t, i, j, k);
		break;
	case 0x744:
		success = handle_case_0x744(t, i, j, k);
		break;
	case 0x750:
		success = handle_case_0x750(t, i, j, k);
		break;
	case 0x788:
		success = handle_case_0x788(t, i, j, k);
		break;
	case 0x7a0:
		success = handle_case_0x7a0(t, i, j, k);
		break;
	case 0x7c0:
		success = handle_case_0x7c0(t, i, j, k);
		break;
	/*
	 * Handle the cases where a single corner is missing.
	 */
	case 0x701:
		success = handle_case_0x701(t, i, j, k);
		break;
	case 0x702:
		success = handle_case_0x702(t, i, j, k);
		break;
	case 0x704:
		success = handle_case_0x704(t, i, j, k);
		break;
	case 0x708:
		success = handle_case_0x708(t, i, j, k);
		break;
	case 0x710:
		success = handle_case_0x710(t, i, j, k);
		break;
	case 0x720:
		success = handle_case_0x720(t, i, j, k);
		break;
	case 0x740:
		success = handle_case_0x740(t, i, j, k);
		break;
	case 0x780:
		success = handle_case_0x780(t, i, j, k);
		break;

	default:
		/*
		 * There's lots of unhandled cases still, but it's not clear
		 * we care.  Let debugging show us what they are so we can
		 * learn if we care.
		 */
		if (t->debug)
			OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
				"Unhandled fingerprint 0x%03x @ %d %d %d\n",
				fp, i, j, k);
		goto out;
	}
	/*
	 * If we successfully handled a case, we may be able to make more
	 * progress at this position, so try again.  Otherwise, even though
	 * we didn't successfully handle a case, we may have installed a
	 * switch into the torus/mesh, so try to install links as well.
	 * Then we'll have another go at the next position.
	 */
	if (success) {
		if (t->debug)
			OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
				"Success on fingerprint 0x%03x @ %d %d %d\n",
				fp, i, j, k);
		goto again;
	} else {
		check_tlinks(t, i, j, k);
		if (t->debug)
			OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
				"Failed on fingerprint 0x%03x @ %d %d %d\n",
				fp, i, j, k);
	}
out:
	return;
}