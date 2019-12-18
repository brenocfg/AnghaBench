__attribute__((used)) static __inline unsigned int
nlm_read_ucore_reg(int reg)
{
	volatile unsigned int *addr = (volatile void *)reg;

	return (*addr);
}